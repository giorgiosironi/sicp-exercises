(define (fibonacci-iter a b i limit)
  (define (sum x y) (+ x y))
  (if (= i limit)
      b
      (fibonacci-iter b
                      (sum a b)
                      (sum i 1)
                      limit)))
(display (fibonacci-iter 1 1 1 10))
(newline)
; is arguments are not memoized when forced, this program will repeatedly calculate sums evaluating the `sum` calls
