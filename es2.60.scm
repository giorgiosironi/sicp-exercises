(define (make-set list)
    list)
; element-of-set? does not change, if at least one element is equal? to x
; it returns #t
; it is O(n) in the worst case
(define (element-of-set? x set)
  (cond ((null? set) false)
        ((equal? x (car set)) true)
        (else (element-of-set? x (cdr set)))))
; adjoin-set is simpler as it does not need to check the presence of x
; it is O(1) instead of O(n)
(define (adjoin-set x set)
  (cons x set))
; union just concatenates so it is O(n1) where n1 = (length set1)
(define (union-set set1 set2)
  (cond ((null? set1) set2)
        (else 
         (cons (car set1)
               (union-set (cdr set1) set2)))))
; intersection seems not to change
; so it is still O(n1*n2)
(define (intersection-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((element-of-set? (car set1) set2)
         (cons (car set1)
               (intersection-set (cdr set1) set2)))
        (else (intersection-set (cdr set1) set2))))
; time complexity is better than in the previous case,
; but space complexity grows with no bounds as union and adjon operations are
; performed.
; Also, since n in the O(...) expressions is the length of the list
; including duplicates, in time this will affect time complexity as well.
; Applications where I would use the duplicate representation:
; - few adjoin-set and union-set, but their performance is important
; - many intersection-set which is neutral with respect to list growth
; - the performance of element-of-set? is not important
