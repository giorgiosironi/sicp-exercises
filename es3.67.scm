; library
(define (display-line text)
  (display text)
  (newline))
(define (display-stream s number-of-elements)
  (if (> number-of-elements 0)
      (begin (display-line (stream-car s))
             (display-stream (stream-cdr s) (- number-of-elements 1)))))
(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))
(define integers (integers-starting-from 1))
(define (interleave . streams)
  (cons-stream (stream-car (car streams))
               (apply interleave
                      (append (cdr streams)
                              (list (stream-cdr (car streams)))))))
; exercise
(define (pairs s t)
  (cons-stream
    (list (stream-car s) (stream-car t))
    (interleave
      (stream-map (lambda (x) (list (stream-car s) x))
                  (stream-cdr t))
      (stream-map (lambda (x) (list x (stream-car t)))
                  (stream-cdr s))
      (pairs (stream-cdr s) (stream-cdr t)))))
(define pairs-of-integers (pairs integers integers))
(display-stream pairs-of-integers 20)
