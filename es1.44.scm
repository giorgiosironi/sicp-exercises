(define (compose f g)
  (lambda (x)
    (f (g x))))
(define (repeated proc n)
  (if (= n 0)
      (lambda (x) x)
      (compose proc
               (repeated proc (- n 1)))))
(define dx 0.1)
(define (smooth proc)
  (lambda (x)
    (/ (+ (proc (- x dx))
          (proc x)
          (proc (+ x dx)))
       3)))
(define (square x) (* x x))
