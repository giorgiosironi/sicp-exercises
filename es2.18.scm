(define (reverse list1)
  (define (reverse-iter source target)
    (if (null? source)
        target
        (reverse-iter (cdr source)
                      (cons (car source)
                            target))))
  (reverse-iter list1 (list)))
