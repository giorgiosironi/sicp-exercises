(load "chapter5.5.scm")
(load "chapter5.4.stack.scm")
;(compile-and-go
;  '(define (fib n)
;     (if (< n 2)
;       n
;       (+ (fib (- n 1)) (fib (- n 2))))))
; compiled version
;; 2
;; (total-pushes = 17 maximum-depth = 5)
;; 3
;; (total-pushes = 27 maximum-depth = 8)
;; 4
;; (total-pushes = 47 maximum-depth = 11)
;; 5
;; (total-pushes = 77 maximum-depth = 14)
(define fibonacci-controller '(
  (assign continue (label fib-done))
  fib-loop
  (test (op <) (reg n) (const 2))
  (branch (label immediate-answer))
  ;; set up to compute Fib(n - 1)
  (save continue)
  (assign continue (label afterfib-n-1))
  (save n)
  ; save old value of n
  (assign n (op -) (reg n) (const 1)); clobber n to n - 1
  (goto (label fib-loop))
  ; perform recursive call
  afterfib-n-1
  ; upon return, val contains Fib(n - 1)
  (restore n)
  (restore continue)
  ;; set up to compute Fib(n - 2)
  (assign n (op -) (reg n) (const 2))
  (save continue)
  (assign continue (label afterfib-n-2))
  (save val)
  ; save Fib(n - 1)
  (goto (label fib-loop))
  afterfib-n-2
  ; upon return, val contains Fib(n - 2)
  (assign n (reg val))
  ; n now contains Fib(n - 2)
  (restore val)
  ; val now contains Fib(n - 1)
  (restore continue)
  ; Fib(n - 1) + Fib(n - 2)
  (assign val (op +) (reg val) (reg n))
  (goto (reg continue))
  immediate-answer
  (assign val (reg n))
  (goto (reg continue))
  fib-done))
(define (run-test n)
    (define fibonacci-machine (make-machine '(n val continue)
                                            (list (list '< <)
                                                  (list '- -)
                                                  (list '+ +))
                                            fibonacci-controller))
    (set-register-contents! fibonacci-machine 'n n)
    (start fibonacci-machine)
    (display n)
    (newline)
    (display (get-register-contents fibonacci-machine 'val))
    (display ((fibonacci-machine 'stack) 'print-statistics))
    (newline)
    (display "---")
    (newline))
(run-test 2)
(run-test 3)
(run-test 4)
(run-test 5)
; special purpose machine version
;  Loading "chapter5.4.stack.scm"... done
;2
;(total-pushes = 4 maximum-depth = 2)
;3
;(total-pushes = 8 maximum-depth = 4)
;4
;(total-pushes = 16 maximum-depth = 6)
;5
;(total-pushes = 28 maximum-depth = 8)
; interpreted version, the less optimized one of the three.
; from es5.29
;(fib 2)
;(total-pushes = 72 maximum-depth = 13)
;(fib 3)
;(total-pushes = 128 maximum-depth = 18)
;(fib 4)
;(total-pushes = 240 maximum-depth = 23)
;(fib 5)
;(total-pushes = 408 maximum-depth = 28)
