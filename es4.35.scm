; amb is not defined in Scheme
(define (amb . choices)
  (cons 'amb choices))
(define (an-integer-between low high)
  (require (<= low high)
  (amb low (an-integer-between (+ low 1)
                               high))))
