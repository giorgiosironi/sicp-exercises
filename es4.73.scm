(define (flatten-stream stream)
  (if (stream-null? stream)
    the-empty-stream
    (interleave
      (stream-car stream)
      (flatten-stream (stream-cdr stream)))))
; if we do not delay the recursion on flatten-stream, we eagerly recur over the whole stream of streams. In case of very long or infinite streams, this will cause performance problems or infinite loops.
