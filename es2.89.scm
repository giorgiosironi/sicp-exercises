; primitives form single term
(define (make-term order coeff) (list order coeff))
(define (order term) (car term))
(define (coeff term) (cadr term))
; current exercise
; data structure is (minimum-order (1 0 0 0 4))
; in order to retain order information also in sublists
(define (make-term-list terms-starting-from-zero-order)
  (make-term-list-of-order 0 terms-starting-from-zero-order))
(define (make-term-list-of-order current-order terms-starting-from-current-order)
  (list current-order terms-starting-from-current-order))
(define (minimum-order term-list)
  (car term-list))
(define (elements term-list)
  (cadr term-list))
(define (the-empty-termlist) (make-term-list '()))
(define (first-term term-list)
  (make-term (minimum-order term-list)
             (car (elements term-list))))
(define (rest-terms term-list)
  (make-term-list-of-order (+ 1
                              (minimum-order term-list))
                           (cdr (elements term-list))))
(define (empty-termlist? term-list) (null? (elements term-list)))



(define (adjoin-term term term-list)
  (define (extend-list-with-one-0 term-list)
    (make-term-list-of-order (minimum-order term-list)
                             '(0)))
  (if (null? (elements term-list))
      (adjoin-term term
                   (extend-list-with-one-0 term-list))
      (if (= (order term)
             (minimum-order term-list))
          (make-term-list-of-order (order term)
                                   ; using + because I don't want to paste sum here
                                   (cons (+ (coeff term)
                                            (coeff (first-term term-list)))
                                         (elements (rest-terms term-list))))
          (make-term-list-of-order (minimum-order term-list)
                                   (cons (coeff (first-term term-list))
                                         (elements (adjoin-term term
                                                                (rest-terms term-list))))))))

(define existing-term-list (make-term-list '(0 1 4 0 0 5)))
