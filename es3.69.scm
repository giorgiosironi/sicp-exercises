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
(define (pairs s t)
  (cons-stream
    (list (stream-car s) (stream-car t))
    (interleave
      (stream-map (lambda (x) (list (stream-car s) x))
                  (stream-cdr t))
      (pairs (stream-cdr s) (stream-cdr t)))))
; exercise
(define (triples s t u)
  ; triangle is the stream of all (s-i, ..., ...)
  ; it is based on `pairs`
  (define (triangle s-i t u)
    (cons-stream
      (list s-i (stream-car t) (stream-car u))
      (interleave
        (stream-map (lambda (x) (list s-i (stream-car t) x))
                    (stream-cdr u))
        (triangle s-i (stream-cdr t) (stream-cdr t)))))
  (cons-stream
    (list (stream-car s) (stream-car t) (stream-car u))
     (interleave
      (triangle (stream-car s) t u)
      (triples (stream-cdr s) (stream-cdr t) (stream-cdr u)))))
(define triples-of-integers (triples integers integers integers))
(define (pythagorean x y z)
  (= (+ (* x x)
        (* y y))
     (* z z)))
(display-line "Sample:")
(display-stream 
  triples-of-integers
  20)
(display-line "Pythagorean:")
(display-stream 
  (stream-filter (lambda (triple) (apply pythagorean triple))
                 triples-of-integers)
  2)
