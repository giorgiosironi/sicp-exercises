; Factorial example: 2
; Registers are shown as if they were a let-form.
; Stack is shown as a list in order of insertion
; entering the first fact-loop
((continue (label fact-done))
 (n 3)
 (val *unassigned*))
()
; first goto, entering second fact-loop
((continue (label after-fact))
 (n 2)
 (val *unassigned*))
((label fact-done) 3)
; second goto, entering third fact-loop
((continue (label after-fact))
 (n 1)
 (val *unassigned*))
((label fact-done) 3 (label after-fact) 2)
; going to base case and exiting it
((continue (label after-fact))
 (n 1)
 (val 1))
((label fact-done) 3 (label after-fact) 2)
; inner after-fact
((continue (label after-fact)) ; overwritten but identical to the previous value
 (n 2)
 (val 2))
((label fact-done) 3)
; outer after-fact
((continue (label fact-done))
 (n 3)
 (val 6))
()
; finished
((continue (label fact-done))
 (n 3)
 (val 6))
()

; Fibonacci example: 3
; entering first fib-loop
((continue (label fib-done))
 (n 3)
 (val *unassigned*))
()
; entering second fib-loop
((continue (label afterfib-n-1))
 (n 2)
 (val *unassigned*))
((label fib-done) 3)
; entering third fib-loop
((continue (label afterfib-n-1))
 (n 1)
 (val *unassigned*))
((label fib-done) 3 (label afterfib-n-1) 2)
; immediate-answer
((continue (label afterfib-n-1))
 (n 1)
 (val 1))
((label fib-done) 3 (label afterfib-n-1) 2)
; first afterfib-n-1
((continue (label afterfib-n-2))
 (n 0)
 (val 1))
((label fib-done) 3 (label afterfib-n-1) 1)
; another fib-loop going to immediate answer
((continue (label afterfib-n-2))
 (n 0)
 (val 0))
((label fib-done) 3 (label afterfib-n-1) 1)
; another afterfib-n-2
((continue (label afterfib-n-1))
 (n 0)
 (val 1)) ; assigned 1 + 0
((label fib-done) 3)
; another afterfib-n-1
((continue (label after-fib-n-2))
 (n 1)
 (val 1))
((label fib-done) 1)
; fib-loop entering the base case
((continue (label after-fib-n-2))
 (n 1)
 (val 1)) ; assigned n == 1
((label fib-done) 1)
; after-fib-n-2
((continue (label fib-done))
 (n 1) ; assigned 1
 (val 2)) ; assigned 1 + 1
()
; reached fib-done
((continue (label fib-done))
 (n 1)
 (val 2)) 
()
