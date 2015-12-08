; old version
(define (stream-flatmap proc s)
  (flatten-stream (stream-map proc s)))
(define (flatten-stream stream)
  (if (stream-null? stream)
    the-empty-stream
    (interleave-delayed
      (stream-car stream)
      (delay (flatten-stream (stream-cdr stream))))))
; simplified version, a.
(define (simple-stream-flatmap proc s)
  (simple-flatten (stream-map proc s)))
(define (simple-flatten stream)
  (stream-map stream-car
              (stream-filter (lambda (s) (not (stream-null? s))) stream)))
; b. I guess the removal of the delay can make a difference in theory, but don't see a problem
