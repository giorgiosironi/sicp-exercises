from subprocess import Popen, PIPE, STDOUT
import unittest

class End2endTest(unittest.TestCase):
    def setUp(self):
        self._p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)

    def test_sum(self):
        self._input('(+ 42 43)')

        output_lines = self._stdout_data.split("\n")

        self.assertEqual([l for l in output_lines if l == "85"], ["85"], "There is no line in the output with the result")

    def test_assignment(self):
        self._input('(define answer 42)')

        output_lines = self._stdout_data.split("\n")
        print output_lines

        self.assertEqual([l for l in output_lines if l == "'ok"], ["'ok"], "There is no line in the output with the result")

    def _input(self, line):
        # not very clear how long this waits
        (self._stdout_data, self._stderr_data) = self._p.communicate(input=line)
