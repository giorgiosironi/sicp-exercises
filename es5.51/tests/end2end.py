from subprocess import Popen, PIPE, STDOUT
p = Popen(['./main'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
# not very clear how long this waits
(stdout_data, stderr_data) = p.communicate(input='(+ 42 43)')

#print stderr_data
output_lines = stdout_data.split("\n")
#print output_lines

assert len([l for l in output_lines if l == "85"]) == 1, "There is no line in the output with the result"
