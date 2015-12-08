; we can only consider the pairs where p1 comes before p2 according to some
; consistent order
(define (comes-before p1 p2)
  (...))
; this way only one of the two duplicated pairs can satisfy the new rule
(rule (lives-near-single ?p1 ?p2)
      (and (lives-near ?p1 ?p2)
           (lisp-value (comes-before ?p1 ?p2))))
