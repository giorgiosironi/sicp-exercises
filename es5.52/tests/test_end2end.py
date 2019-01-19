from subprocess import Popen, PIPE, STDOUT
import unittest

class End2endTest(unittest.TestCase):
    def setUp(self):
        self._p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
        self.maxDiff = None

    def test_integer(self):
        self._input('42')
        self._assertOutput([])
        self._assertErr([
            '[a] operation: initialize-stack',
            '[a] make_perform: Operation-InitializeStack',
            '[a] (assign env (op get-global-environment))',
            '[a] make_assign (op): get-global-environment',
            '[a] (assign val (const 42))',
            '[a] make_assign (const): 42',
            '[e] Perform: Operation-InitializeStack []',
            '[e] Assign (env): Operation-GetGlobalEnvironment',
            '[e] Assign result: Environment',
            '[e] Assign (val): 42',
            'End of controller'
        ])

    def test_string(self):
        self._input('"ab"')
        self._assertOutput([])
        self._assertInErr('[e] Assign (val): "ab"')

    def test_float(self):
        self._input('1.2')
        self._assertOutput([])
        self._assertInErr('[e] Assign (val): 1.200000')

    def test_boolean(self):
        self._input('(display #f)')
        self._assertOutput(['#f'])

    def test_symbol(self):
        self._input('\'foo')
        self._assertOutput([])
        self._assertInErr('[e] Assign (val): foo')

    def test_list(self):
        self._input('(list 42 43)')
        self._assertOutput([])
        self._assertInErr('[e] Assign (proc): Operation-LookupVariableValue (const list) (reg env)')
        self._assertInErr('[e] Assign result: (primitive PrimitiveProcedure:list)')
        self._assertInErr('[e] Assign (val): Operation-ApplyPrimitiveProcedure (reg proc) (reg argl)')
        self._assertInErr('[e] Assign result: (42 43)')

    def test_quoted_list(self):
        self._input('(display \'(42 43))')
        self._assertOutput(['(42 43)'])

    def test_sum_as_primitive_procedure(self):
        self._input('(display (+ 42 43))')
        self._assertOutput(['85'])

    def test_assignment(self):
        self._input(
            "(begin (set! answer 42) (display answer))",
        )
        self._assertOutput(['42'])

    def test_definition_variable(self):
        self._input(
            "(define answer 42)",
        )
        self._assertOutput([])
        self._assertErr([
            '[a] operation: initialize-stack',
            '[a] make_perform: Operation-InitializeStack',
            '[a] (assign env (op get-global-environment))',
            '[a] make_assign (op): get-global-environment',
            '[a] (assign val (const 42))',
            '[a] make_assign (const): 42',
            '[a] (perform (op define-variable!) (const answer) (reg val) (reg env))',
            '[a] operation: define-variable!',
            '[a] make_perform: Operation-DefineVariable',
            '[a] operands: ((const answer) (reg val) (reg env))',
            '[a] vector: 3',
            '[a] (assign val (const ok))',
            '[a] make_assign (const): ok',
            '[e] Perform: Operation-InitializeStack []',
            '[e] Assign (env): Operation-GetGlobalEnvironment',
            '[e] Assign result: Environment',
            '[e] Assign (val): 42',
            '[e] Perform: Operation-DefineVariable [answer, 42, Environment, ]',
            '[e] Assign (val): ok',
            'End of controller',
        ])

    def test_definition_function(self):
        self._input(
            "(begin (define (id x) x) (display (id 42)))",
        )
        self._assertOutput(['42'])

    def test_sum_as_compound_procedure(self):
        self._input(
            "(begin (define (sum x y) (+ x y)) (display (sum 20 22)))"
        )
        self._assertOutput(['42'])

    def test_if_constant_condition(self):
        self._input(
            "(display (if #t 'first 'second))",
        )
        self._assertOutput([
            "first",
        ])

    def test_if_compute_condition_consequent(self):
        self._input(
            "(display (if (= 42 42) 'first 'second))",
        )
        self._assertOutput([
            "first",
        ])

    def test_if_compute_condition_alternative(self):
        self._input(
            "(display (if (= 42 43) 'first 'second))",
        )
        self._assertOutput([
            "second",
        ])

    def test_cond_transformed_to_if(self):
        self._input(
            "(display (cond (#f 'first) (#t 'second)))",
        )
        self._assertOutput([
            "second",
        ])

    def test_let_transformed_to_combination(self):
        self._input(
            "(display (let ((first 42) (second 43)) (+ first second)))",
        )
        self._assertOutput([
            "85",
        ])

    def test_begin(self):
        self._input(
            "(display (begin 'first 'second))",
        )
        self._assertOutput([
            "second",
        ])

    def test_lambda(self):
        self._input(
            "(display ((lambda (n) (* 2 n)) 5))",
        )
        self._assertOutput([
            "10",
        ])

    def test_factorial(self):
        self._input(
            "(begin (define (factorial n) (if (= n 0) 1 (* (factorial (- n 1)) n))) (display (factorial 6)))"
        )
        self._assertOutput(['720'])

    def test_multiple_instructions(self):
        self._input('(display 1) (display 2)')
        self._assertOutput(['12'])

    def test_multiple_instructions_multiple_lines(self):
        self._input("(display 1)\n(display 2)")
        self._assertOutput(['12'])

    def _input(self, *lines):
        # not very clear how long this waits
        (self._stdout_data, self._stderr_data) = self._p.communicate(input="\n".join(lines))

    def _output(self):
        output_lines = self._stdout_data.split("\n")
        return [l for i, l in enumerate(output_lines) if l != '']

    def _err(self):
        err_lines = self._stderr_data.split("\n")
        err_indexes = []
        for index, line in enumerate(err_lines):
            err_indexes.append(index + 1)
        return [l for i, l in enumerate(err_lines) if i in err_indexes and l != ""]

    def _assertOutput(self, output):
        actual_output = self._output()
        self.assertEqual(
            actual_output,
            output,
            "\nSTDOUT: %s\nSTDERR: %s" % (self._stdout_data, self._stderr_data)
        )

    def _assertErr(self, err):
        actual_err = self._err()
        self.assertEqual(
            actual_err,
            err,
        )

    def _assertInErr(self, line):
        actual_err = self._err()
        self.assertIn(
            line,
            actual_err
        )

