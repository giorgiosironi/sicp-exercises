from subprocess import Popen, PIPE, STDOUT
import unittest

class End2endTest(unittest.TestCase):
    def setUp(self):
        self._p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)

    def test_sum(self):
        self._input('(+ 42 43)')
        self.assertEqual(self._output(), ['85'])

    def test_assignment(self):
        self._input("(define answer 42)", "answer")
        self.assertEqual(
            self._output(),
            [
                "'ok",
                "42",
            ]
        )

    def test_compound_procedures(self):
        self._input("(define (sum x y) (+ x y))", "(sum 20 22)")
        self.assertEqual(
            self._output(),
            [
                "'ok",
                "42",
            ]
        )

    def _input(self, *lines):
        # not very clear how long this waits
        (self._stdout_data, self._stderr_data) = self._p.communicate(input="\n".join(lines))

    def _output(self):
        output_lines = self._stdout_data.split("\n")
        output_indexes = []
        for index, line in enumerate(output_lines):
            if '>>> ";;; EC-Eval value:"' == line:
                output_indexes.append(index + 1)
        #self.assertNotEmpty(output_indexes)
        return [l for i, l in enumerate(output_lines) if i in output_indexes]


