; library
(define (display-line text)
  (display text)
  (newline))
(define (display-stream s number-of-elements)
  (if (> number-of-elements 0)
      (begin (display-line (stream-car s))
             (display-stream (stream-cdr s) (- number-of-elements 1)))))
; exercise
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
(define sense-data (list->stream '(1 2 1.5 -0.1 1 0.5 -0.1 -2 -3 -2 -0.5 0.2 3 4)))
(define (make-zero-crossings input-stream last-value last-value-avpt)
  (let ((avpt (/ (+ (stream-car input-stream) last-value) 2)))
    (cons-stream (sign-change-detector avpt last-value-avpt)
                 (make-zero-crossings (stream-cdr input-stream)
                                      (stream-car input-stream)
                                      avpt))))
(display-stream (make-zero-crossings sense-data 0 0) 13)
