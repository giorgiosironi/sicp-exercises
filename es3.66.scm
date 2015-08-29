; library
(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))
(define integers (integers-starting-from 1))
(define (interleave s1 s2)
  (if (stream-null? s1)
      s2
      (cons-stream (stream-car s1)
                   (interleave s2 (stream-cdr s1)))))
(define (pairs s t)
  (cons-stream
    (list (stream-car s) (stream-car t))
    (interleave
      (stream-map (lambda (x) (list (stream-car s) x))
                  (stream-cdr t))
      (pairs (stream-cdr s) (stream-cdr t)))))
(define pairs-of-integers (pairs integers integers))
; empirical research
(define (search element stream)
  (define (iterate element stream position)
    (if (equal? element
                (stream-car stream))
        position
        (iterate element
                 (stream-cdr stream)
                 (+ 1 position))))
  (iterate element stream 0))
