(define (cont-frac n d k)
  (cont-frac-step n d k 1))
(define (cont-frac-step n d k i)
  (if (> i k)
      0
      (/ (n i)
         (+ (d i)
            (cont-frac-step n d k (+ i 1))))))
(define (tan-cf x k)
  (define (n i)
    (if (= i 1)
        x
        (- 0 (* x x))))
  (define (d i)
    (- (* 2 i)
       1))
  (cont-frac n d k))
      
