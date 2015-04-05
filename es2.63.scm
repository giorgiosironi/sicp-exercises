; primitives of set-as-trees
(define (entry tree) (car tree))
(define (left-branch tree) (cadr tree))
(define (right-branch tree) (caddr tree))
(define (make-tree entry left right)
  (list entry left right))
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((= x (entry set)) true)
        ((< x (entry set))
         (element-of-set? x (left-branch set)))
        ((> x (entry set))
         (element-of-set? x (right-branch set)))))
(define (adjoin-set x set)
  (cond ((null? set) (make-tree x '() '()))
        ((= x (entry set)) set)
        ((< x (entry set))
         (make-tree (entry set)
                    (adjoin-set x (left-branch set))
                    (right-branch set)))
        ((> x (entry set))
         (make-tree (entry set)
                    (left-branch set)
                    (adjoin-set x (right-branch set))))))
; exercise
(define (tree->list-1 tree)
  (if (null? tree)
    '()
    (append (tree->list-1 (left-branch tree))
            (cons (entry tree)
                  (tree->list-1 (right-branch tree))))))
(define (tree->list-2 tree)
  (define (copy-to-list tree result-list)
    (if (null? tree)
      result-list
      (copy-to-list (left-branch tree)
                    (cons (entry tree)
                          (copy-to-list (right-branch tree)
                                        result-list)))))
  (copy-to-list tree '()))
; example from figure 2.16
; on these 3 trees tree->list-1 and tree->list-2 produce the same result
(define (leaf x) (make-tree x (list) (list)))
(define tree-figure-1
  (make-tree 7
             (make-tree 3
                        (leaf 1)
                        (leaf 5))
             (make-tree 9
                        (list)
                        (leaf 11))))
(define tree-figure-2
  (make-tree 3
             (leaf 1)
             (make-tree 7
                        (leaf 5)
                        (make-tree 9
                                   (list)
                                   (leaf 11))))) 
(define tree-figure-3
  (make-tree 5
             (make-tree 3
                        (leaf 1)
                        (list))
             (make-tree 9
                        (leaf 7)
                        (leaf 11))))
; tree->list-1 produce a tree recursive process
; the number of recursive calls is proportional to the number of elements in the tree
; however append is called each time on a growing left-branch transformed to list
; 1. each level of the tree has 1, 2, 4, 8, ... left-branches
; 2. each left-branch contains n/2, n/4, n/8, n/16, ... items (actually with +1 for each entry when you go up, but O()-speaking is the same
; 3. there are log(n) levels of a balanced tree
; so the average case of a balanced tree is O(n log n)
; the worst case is O(n^2) for a tree with n levels, resembling a list
; instead tree->list-2 deals with the left branch by cons-ing each of its elements
; so time should be O(n)
