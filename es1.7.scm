(define (sqrt-iter guess old-guess x)
  (if (good-enough? guess old-guess)
      guess
      (sqrt-iter (improve guess x)
                 guess
                 x)))

; works for x == 10000*10000 while the old one recursed indefinitely
(define (good-enough? guess old-guess)
  (< (abs (- guess old-guess)) 0.0001))

(define (improve guess x)
  (average guess (/ x guess)))

(define (average x y)
  (/ (+ x y) 2))
