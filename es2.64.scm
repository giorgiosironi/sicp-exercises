; primitives of trees
(define (entry tree) (car tree))
(define (left-branch tree) (cadr tree))
(define (right-branch tree) (caddr tree))
(define (make-tree entry left right)
  (list entry left right))
; exercise code
(define (list->tree elements)
  (car (partial-tree elements (length elements))))
(define (partial-tree elts n)
  (display elts)
  (display n)
  (newline)
  (if (= n 0)
    ; empty tree and all elements remain
    (cons '() elts)
    ; the number of elements in the left branch
    (let ((left-size (quotient (- n 1) 2)))
      (let ((left-result (partial-tree elts left-size)))
              ; the left branch
        (let ((left-tree (car left-result))
              ; the elements not in the left branch
              ; that should be assigned to the entry
              ; or to the right branch
              (non-left-elts (cdr left-result))
              ; the number of elements in the right branch
              (right-size (- n (+ left-size 1))))
                ; the first of the remaining elements becomes the entry
          (let ((this-entry (car non-left-elts))
                (right-result (partial-tree (cdr non-left-elts)
                                            right-size)))
                  ; the right branch
            (let ((right-tree (car right-result))
                  (remaining-elts (cdr right-result)))
                ; composing the tree to return 
                ; and the elements that did not fit in both 
                ; branches nor in the entry
              (cons (make-tree this-entry left-tree right-tree)
                    remaining-elts))))))))
; tree created by (list->tree '(1 3 5 7 9 11))
; (5 
;       (1
;           ()
;           (3 () ()))
;       (9 
;           (7 () ())
;           (11 () ())))
; at each recursion level the size of the list is divided into 2
; after 1 is subtracted for the current entry
; so from a list of 6 we get two subtrees of 2 and 3 elements
; when there are 2 elements we get an empty left and 1-element right subtree
; when there are 3 elements we get both 1-element subtrees
; the trees composed by 1 element are a tree with 0-element subtrees
