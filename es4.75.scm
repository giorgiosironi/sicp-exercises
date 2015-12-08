; implementation for not
(define (negate operands frame-stream)
  (stream-flatmap
    (lambda (frame)
      (if (stream-null? (qeval (negated-query operands)
                               (singleton-stream frame)))
        (singleton-stream frame)
        the-empty-stream))
    frame-stream))
(put 'not 'qeval negate)
; implementation for unique
(define (stream-unique? stream)
  (cond ((stream-null? stream)
         #f)
        ((stream-null? (stream-cdr stream))
         #t)
        (else
         #f)))
(define (uniquely-asserted operands frame-stream)
  (stream-flatmap
    (lambda (frame)
      (if (stream-unique? (qeval (car operands)
                                 (singleton-stream frame)))
        (singleton-stream frame)
        the-empty-stream))
    frame-stream))
(put 'unique 'qeval uniquely-asserted)
; query
(unique (supervisor ?p1 ?p2))
