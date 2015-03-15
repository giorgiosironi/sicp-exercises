(define (accumulate proc initial sequence)
  (if (null? sequence)
      initial
      (proc (car sequence)
            (accumulate proc initial (cdr sequence)))))
(define (horner-eval x coefficient-sequence)
  (accumulate (lambda (this-coeff higher-terms) (+ (* x higher-terms)
                                                   this-coeff))
              0
              coefficient-sequence))
