(define (same-parity . arguments)
  (define (same-parity-list list1)
    (cond ((null? list1)
           list1)
          ((= (length list1)
              1)
           list1)
          (else
           (cons (car list1)
                 (same-parity-list (cdr (cdr list1)))))))
  (same-parity-list arguments))

