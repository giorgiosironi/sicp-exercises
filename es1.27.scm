(define (expmod base exp m)
  (cond ((= exp 0) 1)
        ((even? exp)
         (remainder (square (expmod base (/ exp 2) m))
                    m))
        (else
          (remainder (* base (expmod base (- exp 1) m))
                     m))))
(define (full-fermat-test n)
  (full-fermat-test-iter 1 n))
; #t for prime numbers (usually), tested on 2-3-5-7-11
; #f for other numbers, tested on 4-6-8-9-10
; #t for 561, 1105, 1729, 2465, 2821, 6601 (Carmichael numbers)
;     which however are not prime, e.g. 561=3*11*17
(define (full-fermat-test-iter a n)
  (define (try-it a)
    (= (expmod a n n) a))
  (cond ((= a n) #t)
        ((try-it a) (full-fermat-test-iter (+ a 1) n))
        (else #f))) 
