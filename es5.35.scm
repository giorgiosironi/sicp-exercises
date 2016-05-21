(load "chapter5.5.scm")
(define expression '(define (f x)
                      (+ x (g (+ x 2)))))
(dump (caddr (compile expression 'val 'next)))


