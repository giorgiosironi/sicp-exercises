(define (adjoin-set x set)
  (if (null? set)
      (list x)
      (let ((current (car set)))
        (cond ((= x current) set)
              ((< x current) (cons x set))
              ((> x current) (cons current
                                   (adjoin-set x
                                               (cdr set))))))))
