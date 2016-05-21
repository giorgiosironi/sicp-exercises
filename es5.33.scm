(load "chapter5.5.scm")
(define factorial-definition '(define (factorial-alt n)
                                (if (= n 1)
                                  1
                                  (* n (factorial-alt (- n 1))))))
(dump (caddr (compile factorial-definition 'val 'next)))


