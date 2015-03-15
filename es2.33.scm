(define (accumulate proc initial sequence)
  (if (null? sequence)
      initial
      (accumulate proc
                  (proc initial
                        (car sequence))
                  (cdr sequence))))
(define (map p sequence)
  (accumulate (lambda (x y) (append x
                                    (list (p y))))
              (list)
              sequence))
