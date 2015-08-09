; library
(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))
(define integers (integers-starting-from 1))
(define (add-streams s1 s2)
  (cons-stream (+ (stream-car s1)
                  (stream-car s2))
               (add-streams (stream-cdr s1)
                               (stream-cdr s2))))
(define (scale-stream s n)
  (cons-stream (* (stream-car s)
                  n)
               (scale-stream (stream-cdr s)
                             n)))
(define (divide-streams s1 s2)
  (cons-stream (/ (stream-car s1)
                  (stream-car s2))
               (divide-streams (stream-cdr s1)
                               (stream-cdr s2))))
(define (integrate-series series)
  (divide-streams
    series
    integers))
(define cosine-series
  (cons-stream 1 (integrate-series (scale-stream sine-series -1))))
(define sine-series
  (cons-stream 0 (integrate-series cosine-series)))
(define (mul-series s1 s2)
  (cons-stream 
    (* (stream-car s1)
       (stream-car s2))
    (add-streams
      (add-streams (scale-stream (stream-cdr s1)
                                 (stream-car s2))
                   (scale-stream (stream-cdr s2)
                                 (stream-car s1)))
      (cons-stream 0
                   (mul-series (stream-cdr s1)
                               (stream-cdr s2))))))
(define exp-series
  (cons-stream 1 (integrate-series exp-series)))
; exercise
(define (invert-unit-series series)
  (define x
    (cons-stream 1
                 (scale-stream (mul-series (stream-cdr series)
                                           x)
                               -1)))
  x)
