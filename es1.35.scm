(define (transformation x)
  (+ 1
     (/ 1 x)))
(define (fixed-point f first-guess)
  (define tolerance 0.00001)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (if (close-enough? guess next)
        next
        (try next))))
  (try first-guess))
; x -> 1 + 1/x
; substitute a/b as x:
; a/b == 1 + 1/(a/b)
; a/b == (a/b + 1)/(a/b)
; a2/b2 == a/b + 1
; a2 == ab + b2
; a == (ab+b2)/a
; a == b+b2/a
; a/b == 1+b/a
; a/b == (a+b)/a
; which is the definition of golden ratio
; (exact->inexact (fixed-point transformation 1))
