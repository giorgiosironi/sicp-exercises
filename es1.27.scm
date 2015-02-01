(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        (else
          (remainder (* base (expmod base (- exp 1) m))
                     m))))
(define (full-fermat-test n)
  ; iterate i from 2 to n-1
  (define (try-it a)
    (= (expmod a n n) a))
  (try-it i))
