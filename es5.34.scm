(load "chapter5.5.scm")
(define factorial-definition '(define (factorial n)
                                (define (iter product counter)
                                  (if (> counter n)
                                    product
                                    (iter (* counter product)
                                          (+ counter 1))))
                                (iter 1 1)))
(dump (caddr (compile factorial-definition 'val 'next)))


