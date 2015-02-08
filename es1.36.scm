(define (fixed-point f first-guess)
  (define tolerance 0.00001)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess)))
      (newline)
      (display next)
      (if (close-enough? guess next)
        next
        (try next))))
  (try first-guess))

(define (fixed-point-damped f first-guess)
  (define tolerance 0.00001)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (average a b)
    (/ (+ a b)
       2))
  (define (try guess)
    (let ((next (f guess)))
      (newline)
      (display next)
      (if (close-enough? guess next)
        next
        (try (average next guess)))))
  (try first-guess))

(define (transformation x)
  (/ (log 1000)
     (log x)))

; given 2 as initial guess
; fixed-point: 35 steps
; fixed-point-damped: 10 steps
