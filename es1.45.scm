(define (compose f g)
  (lambda (x)
    (f (g x))))
(define (repeated proc n)
  (if (= n 0)
      (lambda (x) x)
      (compose proc
               (repeated proc (- n 1)))))
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
(define (average-damp proc)
  (lambda (x)
    (/ (+ x
          (proc x))
       2)))
(define (n-root n dampings x)
  (define (transformed y)
    (/ x
       (expt y 
             (- n 1))))
  (fixed-point ((repeated average-damp dampings) transformed) 1.0))
(define (square x) (* x x))
; (n-root 2 1 ...) converges
; (n-root 3 1 ...) converges
; (n-root 4 1 ...) does not converge
; (n-root 4 2 ...) converges
; (n-root 5 2 ...) converges
; (n-root 6 2 ...) converges
; (n-root 7 2 ...) converges
; (n-root 8 2 ...) does not converge
; (n-root 8 3 ...) converges
; ...
; (n-root 15 3 ...) converges
; (n-root 16 3 ...) does not converge
; (n-root 16 4 ...) converges
; ...
; (n-root 31 4 ...) converges
; (n-root 32 4 ...) does not converge
; (n-root 32 5 ...) converges
; It seems we need a number of dampings which is O(log(n)), in particular here
; it is >= (floor (log2 n))
