(define (show x)
  (display-line x)
  x)
(define (display-line x)
  (display x)
  (newline))
(define (stream-enumerate-interval low high)
  (if (> low high)
    the-empty-stream
    (cons-stream
      low
      (stream-enumerate-interval (+ low 1) high))))

; evaluations
(define x (stream-map show (stream-enumerate-interval 0 10)))
; shows only '0' because x is a new stream and as such only its car element is computed
; until stream-cdr is used on x no other elements will be shown
(stream-ref x 5)
; prints 1, 2, 3, 4, 5
; because 0 was already evaluated and we get to the 6th element of x
; (indexes are 0-based)
(stream-ref x 7)
; prints 6, 7 for the same reasoning as the previous stream-ref
