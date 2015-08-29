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
  (interleave
    (stream-map (lambda (x) (list (stream-car s) x))
                t)
    (pairs (stream-cdr s) (stream-cdr t))))
; this gives "Aborting!: maximum recursion depth exceeded
(define pairs-of-integers (pairs integers integers))
; it must give so while computing the first element, which is the only one
; eagerly computed in a stream
; to calculate the first element, it must execute `interleave` and hence evaluate its arguments to produce the two input streams
; - the first argument is no problem as it's a stream starting with (1, 1)
; - the second argument however, recurs into pairs which again starts to 
;   evalute a new version of itself...
