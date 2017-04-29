from subprocess import Popen, PIPE, STDOUT
import unittest

class End2endTest(unittest.TestCase):
    def setUp(self):
        self._p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)

    def test_integer(self):
        self._input('42')
        self._assertOutput(['42'])

    def test_string(self):
        self._input('"ab"')
        self._assertOutput(['"ab"'])

    def test_float(self):
        self._input('1.2')
        self._assertOutput(['1.200000'])

    def test_boolean(self):
        self._input('#f')
        self._assertOutput(['#f'])

    def test_symbol(self):
        self._input('\'foo')
        self._assertOutput(['foo'])

    def test_list(self):
        self._input('(list 42 43)')
        self._assertOutput(['(42 43)'])

    def test_sum_as_primitive_procedure(self):
        self._input('(+ 42 43)')
        self._assertOutput(['85'])

    def test_assignment(self):
        self._input(
            "(define answer 42)",
            "answer"
        )
        self._assertOutput([
            "ok",
            "42",
        ])

    def test_sum_as_compound_procedure(self):
        self._input(
            "(define (sum x y) (+ x y))",
            "(sum 20 22)"
        )
        self._assertOutput([
            "ok",
            "42",
        ])

    def test_if(self):
        self._input(
            "(if (= 42 42) 'equal 'wrong)",
        )
        self._assertOutput([
            "equal",
        ])

    def test_lambda(self):
        self._input(
            "((lambda (n) (* 2 n)) 5)",
        )
        self._assertOutput([
            "10",
        ])

    def test_factorial(self):
        self._input(
            "(define (factorial n) (if (= n 0) 1 (* (factorial (- n 1)) n)))",
            "(factorial 6)"
        )
        self._assertOutput([
            "ok",
            "720",
        ])

    def _input(self, *lines):
        # not very clear how long this waits
        (self._stdout_data, self._stderr_data) = self._p.communicate(input="\n".join(lines))

    def _output(self):
        output_lines = self._stdout_data.split("\n")
        output_indexes = []
        for index, line in enumerate(output_lines):
            if '>>> ";;; EC-Eval value:"' == line:
                output_indexes.append(index + 1)
        return [l for i, l in enumerate(output_lines) if i in output_indexes]

    def _assertOutput(self, output):
        actual_output = self._output()
        self.assertEqual(
            actual_output,
            output,
            "STDOUT: %s\nSTDERR: %s" % (self._stdout_data, self._stderr_data)
        )

