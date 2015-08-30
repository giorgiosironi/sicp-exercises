; library
(define (display-line text)
  (display text)
  (newline))
(define (display-stream s number-of-elements)
  (if (> number-of-elements 0)
      (begin (display-line (stream-car s))
             (display-stream (stream-cdr s) (- number-of-elements 1)))))
(define (sign-change-detector new-value last-value)
  (define (sign value)
    (if (>= value 0)
        1
        -1))
  (let ((new-sign (sign new-value))
        (last-sign (sign last-value)))
    (if (eq? new-sign last-sign)
        0
        new-sign)))
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
; exercise
(define sense-data (list->stream '(1 2 1.5 -0.1 1 0.5 -0.1 -2 -3 -2 -0.5 0.2 3 4)))
(display-line "data")
(display-stream sense-data 11)
(define (zero-crossings sensor)
  (stream-map
    sign-change-detector
    sensor
    (cons-stream 0 sensor)))
(define (smooth sensor)
  (scale-stream
    (add-streams
      sensor
      (cons-stream (stream-car sensor) sensor))
    0.5))
(display-line "original zero-crossings")
(display-stream (zero-crossings sense-data) 13)
(display-line "smoothed signal zero-crossings")
(display-stream (zero-crossings (smooth sense-data)) 13)
