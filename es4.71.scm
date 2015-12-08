; original
(define (simple-query query-pattern frame-stream)
  (stream-flatmap
    (lambda (frame)
      (stream-append-delayed
        (find-assertions query-pattern frame)
        (delay (apply-rules query-pattern frame))))
    frame-stream))
; incorrect proposal
(define (simple-query query-pattern frame-stream)
  (stream-flatmap
    (lambda (frame)
      (stream-append (find-assertions query-pattern frame)
                     (apply-rules query-pattern frame)))
    frame-stream))
(define (disjoin disjuncts frame-stream)
  (if (empty-disjunction? disjuncts)
    the-empty-stream
    (interleave
      (qeval (first-disjunct disjuncts) frame-stream)
      (disjoin (rest-disjuncts disjuncts) frame-stream))))
; without a delayed operation, we will eagerly try to expand rules over the query or, in the case of disjoin, perform evaluations to verify all branches of an or. Consider:
(son Adam ?s)
; would try to perform unification of son with all rules even if it's just a database assertion. By delaying the operation, we avoid doing this until necessary in the evaluation.
; Reading around, it also seems that dealying postpones some infinite loop like in the Mickey-Minnie case (the infinite loop will nevertheless happen)
