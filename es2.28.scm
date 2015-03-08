(define (fringe tree)
  (cond ((null? tree)
         (list))
        ((pair? tree)
         (append (fringe (car tree))
                 (fringe (cdr tree))))
        (else (list tree))))

(define x (list (list 1 2) (list 3 4)))
