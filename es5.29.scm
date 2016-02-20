; previously on SICP: redefine the stack to measure statistics
(load "chapter5.4.scm")
(load "chapter5.4.stack.scm")

; procedures to run (fib n)
(add-primitive-procedure '< <)
(add-primitive-procedure '+ +)
(add-primitive-procedure '- -)

(start eceval)
; depth of the stack
;
; ;;; EC-Eval input:
;
; depth = 3 + 5*n
;
; number of pushes 
;
; fib 2
; total-pushes = 72 
; fib 3
; total-pushes = 128
; fib 4
; total-pushes = 240
; fib 5
; total-pushes = 408
; fib 6
; total-pushes = 688
; fib 7
; total-pushes = 1136
;
; S(n) = S(n-1) + S(n-2) + k?
; The number of pushes is equal to the number of pushes of the two subproblems
; plus the overhead of summing up the two results
; System needs at least two equations
; ; 240 = 72 + 128 + k = 200 + k
; ; 1136 = 688 + 408 + k = 1096 + k
; k = 40
; S(n) = S(n-1) + S(n-2) + 40
;
;(fib 2)
;(total-pushes = 72 maximum-depth = 13)
;;;; EC-Eval value:
;1
;
;(fib 3)
;(total-pushes = 128 maximum-depth = 18)
;2
;
;(fib 4)
;(total-pushes = 240 maximum-depth = 23)
;3
;
;(fib 5)
;(total-pushes = 408 maximum-depth = 28)
;5
;
;(fib 6)
;(total-pushes = 688 maximum-depth = 33)
;8
;
;(fib 7)
;(total-pushes = 1136 maximum-depth = 38)
;13
;
; Hypothesis: S(n) = a*Fib(n+1) + b
; ; 688 = a*13+b
; ; 408 = a*8+b
; subtracting
; 280 = a*5
; a = 56
; 408 = 56*8+b
; b = -40

