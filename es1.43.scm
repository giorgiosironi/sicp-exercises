(define (compose f g)
  (lambda (x)
    (f (g x))))
(define (repeated proc n)
  (if (= n 0)
      (lambda (x) x)
      (compose proc
               (repeated proc (- n 1)))))
