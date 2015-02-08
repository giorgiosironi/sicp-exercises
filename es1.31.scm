(define (product term a next b)
  (if (> a b)
    1
    (* (term a)
       (product term (next a) next b))))
(define (factorial n)
  (define (identity x) x)
  (define (inc x) (+ 1 x))
  (product identity 1 inc n))
