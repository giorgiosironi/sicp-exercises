(load "chapter5.5.scm")
(load "chapter5.4.scm")
(define expression '(begin
                      (define (id x)
                        (debug x)
                        x)
                      (define (devnull arg1 arg2) 'nothing)
                      (devnull (id "A") (id "B"))))
(add-operation 'make-compiled-procedure make-compiled-procedure)
(add-operation 'compiled-procedure-env compiled-procedure-env)
(add-operation 'compiled-procedure-entry compiled-procedure-entry)
(add-operation 'list list)
(add-operation 'cons cons)
(add-primitive-procedure 'debug (lambda (arg)
                        (display "DEBUG: ")
                        (display arg)
                        (newline)))


(define compiled-program (caddr (compile expression 'val 'next)))

(define linked-program (append
                         '(
                           (perform (op initialize-stack))
                           (assign env (op get-global-environment))
                         )
                         compiled-program))

(define machine-of-compiled-program (make-machine eceval-registers
                             machine-operations
                             linked-program))
(start machine-of-compiled-program)

