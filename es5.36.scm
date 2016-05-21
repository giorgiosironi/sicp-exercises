(load "chapter5.5.scm")
(define expression '(begin
                      (define (id x)
                        (debug x)
                        x)
                      (define (devnull arg1 arg2) 'nothing)
                      (devnull (id "A") (id "B"))))
(compile-and-execute expression)

