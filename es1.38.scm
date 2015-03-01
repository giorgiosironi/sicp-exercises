(define (cont-frac n d k)
  (cont-frac-step n d k 1))
(define (cont-frac-step n d k i)
  (if (> i k)
      0
      (/ (n i)
         (+ (d i)
            (cont-frac-step n d k (+ i 1))))))
(define (n i)
  1)
(define (d i)
  (let ((r (remainder i 3))
        (q (quotient i 3)))
    (if (= r 2)
        (* 2 (+ q 1))
        1)))
(define (e k)
  (+ 2.0
     (cont-frac n d k)))