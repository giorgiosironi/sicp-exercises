from subprocess import Popen, PIPE, STDOUT
import unittest

class End2endTest(unittest.TestCase):
    def setUp(self):
        self._p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)

    def test_sum(self):
        self._input('(+ 42 43)')
        self.assertEqual(self._output(), '85')

    def test_assignment(self):
        self._input('(define answer 42)')
        self.assertEqual(self._output(), "'ok")
        # ValueError: I/O operation on closed file
        #self._input('answer')
        #self.assertEqual(self._output(), "'ok")

    def _input(self, line):
        # not very clear how long this waits
        (self._stdout_data, self._stderr_data) = self._p.communicate(input=line)

    def _output(self):
        output_lines = self._stdout_data.split("\n")
        output_index = None
        for index, line in enumerate(output_lines):
            if '>>> ";;; EC-Eval value:"' == line:
                output_index = index + 1
                break
        self.assertIsNotNone(output_index)
        return output_lines[output_index]


