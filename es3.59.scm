; library
(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))
(define integers (integers-starting-from 1))
(define (divide-streams s1 s2)
  (cons-stream (/ (stream-car s1)
                  (stream-car s2))
               (divide-streams (stream-cdr s1)
                               (stream-cdr s2))))
; exercise
(define (integrate-series series)
  (divide-streams
    series
    integers))
