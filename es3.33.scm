(define (averager a b c)
  (let ((s (make-connector))
        (n (make-connector)))
    (adder a b s)
    (multiplier c n s)
    (constant 2 n)
    'ok))
