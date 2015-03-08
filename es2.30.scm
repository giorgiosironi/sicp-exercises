(define (square-tree-recur tree)
  (cond ((null? tree) (list))
        ((not (pair? tree)) (* tree tree))
        (else (cons (square-tree-recur (car tree))
                    (square-tree-recur (cdr tree))))))
(define (square-tree-map tree)
  (map (lambda (sub-tree)
         (if (pair? sub-tree)
           (square-tree-map sub-tree)
           (* sub-tree sub-tree)))
       tree))

(define my-tree
  (list 1
        (list 2 (list 3 4) 5)
        (list 6 7)))
