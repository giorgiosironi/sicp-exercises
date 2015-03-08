(define (last-pair list1)
  (if (null? (cdr list1))
      list1
      (last-pair (cdr list1))))
