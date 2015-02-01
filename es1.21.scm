(define (smallest-divisor n)
  (find-divisor n 2))
(define (find-divisor n test-divisor)
  (cond ((> (square test-divisor) n) n)
        ((divides? n test-divisor) test-divisor)
        (else (find-divisor n (+ 1 test-divisor)))))
(define (divides? a b)
  (= 0 (remainder a b)))

; 199 => 199
; 1999 => 1999
; 19999 => 7
