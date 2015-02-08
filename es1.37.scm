(define (cont-frac n d k)
  (cont-frac-step n d k 1))
(define (cont-frac-step n d k i)
  (if (> i k)
      0
      (/ (n i)
         (+ (d i)
            (cont-frac-step n d k (+ i 1))))))
; (/ 1(cont-frac (lambda (i) 1.0) (lambda (i) 1.0) 32)) gives 1.6180339, good
