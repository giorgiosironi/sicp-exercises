(define (find-cycle x)
  (define (set-insert element set)
    (if (memq element set)
        set
        (cons element set)))
  (define (find-cycle-iter visited queue)
    (if (null? queue)
        #f
        (if (eq? visited
                 (car queue))
            #t
            (find-cycle-iter visited (cdr queue)))))
  ; note only cycles while cdr-ing are interesting for this exercise
  ; there could be a cycle on car-ing e.g. in trees
  (find-cycle-iter (car x) (cdr x)))

; tests
(define finite '(a b c))
(define infinite (cons 'a '()))
(set-cdr! infinite infinite)
