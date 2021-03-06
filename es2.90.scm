; generic operations infrastructure
(define *operation-table* (make-hash-table))
(define (put op types proc)
    (hash-table/put! 
          *operation-table* 
              (list op types) 
                  proc))
(define (get op types)
    (hash-table/get 
          *operation-table* 
              (list op types) 
                  #f))
(define (type-tag exp)
  (cond ((number? exp) 'number)
        (else (car exp))))
(define (contents exp)
  (cond ((number? exp) exp)
        (else (cadr exp))))
(define (attach-tag tag contents)
  (cond ((number? contents) contents)
        (else (list tag contents))))
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (error "Cannot find procedure for these types -- APPLY-GENERIC" (list op type-tags))))))
; term code
(define (make-term order coeff) (list order coeff))
(define (order term) (car term))
(define (coeff term) (cadr term))
; sparse term list code
(define (install-term-list-sparse)
  (define (the-empty-termlist) '())
  (define (first-term term-list) (car term-list))
  (define (rest-terms term-list) (cdr term-list))
  (define (empty-termlist? term-list) (null? term-list))
  (define (adjoin-term term term-list)
    (if (=zero? (coeff term))
      term-list
      (cons term term-list)))
  (put 'the-empty-termlist 'sparse
       (lambda () (attach-tag 'sparse (the-empty-termlist))))
  (put 'first-term '(sparse)
       (lambda (term-list) (first-term term-list)))
  (put 'rest-terms '(sparse)
       (lambda (term-list) (attach-tag 'sparse (rest-terms term-list))))
  (put 'empty-termlist? '(sparse)
       (lambda (term-list) (empty-termlist? term-list)))
  (put 'adjoin-term 'sparse
       (lambda (term term-list) (attach-tag 'sparse (adjoin-term term term-list))))
  'done)
(install-term-list-sparse)
(define (the-empty-termlist-sparse)
  ((get 'the-empty-termlist 'sparse)))
; dense term list code
(define (install-term-list-dense)
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
    (define (zero-fill-left how-many list)
      (if (= how-many 0)
          list
          (cons 0 (zero-fill-left (- how-many 1)
                                  list))))
    (if (null? (elements term-list))
        (adjoin-term term
                     (extend-list-with-one-0 term-list))
        (cond ((= (order term)
                  (minimum-order term-list))
               (make-term-list-of-order (order term)
                                        ; using + because I don't want to paste sum here
                                        (cons (+ (coeff term)
                                                 (coeff (first-term term-list)))
                                              (elements (rest-terms term-list)))))
              ((> (order term)
                  (minimum-order term-list))
               (make-term-list-of-order (minimum-order term-list)
                                        (cons (coeff (first-term term-list))
                                              (elements (adjoin-term term
                                                                     (rest-terms term-list))))))
              ((< (order term)
                  (minimum-order term-list))
               (make-term-list-of-order (order term)
                                        (cons (coeff term)
                                              (zero-fill-left (- (- (minimum-order term-list)
                                                                    (order term))
                                                                 1)
                                                              (elements term-list))))))))
  
  (put 'the-empty-termlist 'dense
       (lambda () (attach-tag 'dense (the-empty-termlist))))
  (put 'first-term '(dense)
       (lambda (term-list) (first-term term-list)))
  (put 'rest-terms '(dense)
       (lambda (term-list) (attach-tag 'dense (rest-terms term-list))))
  (put 'empty-termlist? '(dense)
       (lambda (term-list) (empty-termlist? term-list)))
  (put 'adjoin-term 'dense
       (lambda (term term-list) (attach-tag 'dense (adjoin-term term term-list))))
  'done)
(install-term-list-dense)
(define (the-empty-termlist-dense)
  ((get 'the-empty-termlist 'dense)))
; term-list generic code
; default is sparse
(define (the-empty-termlist)
  ((get 'the-empty-termlist 'sparse)))
(define (first-term term-list)
  (apply-generic 'first-term term-list))
(define (rest-terms term-list)
  (apply-generic 'rest-terms term-list))
(define (empty-termlist? term-list)
  (apply-generic 'empty-termlist? term-list))
(define (adjoin-term term term-list)
  ((get 'adjoin-term (type-tag term-list)) term
                                           (contents term-list)))
(define (make-term-list-from a-empty-term-list terms)
  (define (add-to-term-list term-list terms)
    (cond ((null? terms)
           term-list)
          (else
           (add-to-term-list (adjoin-term (car terms)
                                          term-list)
                             (cdr terms)))))
  (add-to-term-list a-empty-term-list
                    terms))
(define (make-term-list terms)
  (make-term-list-from (the-empty-termlist-sparse) terms))
(define (make-term-list-dense terms)
  (make-term-list-from (the-empty-termlist-dense) terms))
(define (term-list-map proc term-list)
  (if (empty-termlist? term-list)
      (the-empty-termlist)
      (adjoin-term (proc (first-term term-list))
                   (term-list-map proc (rest-terms term-list)))))
(define (add-terms L1 L2)
  (cond ((empty-termlist? L1) L2)
        ((empty-termlist? L2) L1)
        (else
          (let ((t1 (first-term L1)) (t2 (first-term L2)))
            (cond ((> (order t1) (order t2))
                   (adjoin-term
                     t1 (add-terms (rest-terms L1) L2)))
                  ((< (order t1) (order t2))
                   (adjoin-term
                     t2 (add-terms L1 (rest-terms L2))))
                  (else
                    (adjoin-term
                      (make-term (order t1)
                                 (add (coeff t1) (coeff t2)))
                      (add-terms (rest-terms L1)
                                 (rest-terms L2)))))))))

(define (mul-terms L1 L2)
  (if (empty-termlist? L1)
    (the-empty-termlist)
    (add-terms (mul-term-by-all-terms (first-term L1) L2)
               (mul-terms (rest-terms L1) L2))))
(define (mul-term-by-all-terms t1 L)
  (if (empty-termlist? L)
    (the-empty-termlist)
    (let ((t2 (first-term L)))
      (adjoin-term
        (make-term (+ (order t1) (order t2))
                   (mul (coeff t1) (coeff t2)))(mul-term-by-all-terms t1 (rest-terms L))))))

; polynomial code
(define (install-polynomial-package)
  ;; internal procedures
  ;; representation of poly
  (define (make-poly variable term-list)
    (list variable term-list))
  (define (variable p) (car p))
  (define (term-list p) (cadr p))
  (define (variable? x) (symbol? x))
  (define (same-variable? v1 v2)
    (and (variable? v1) (variable? v2) (eq? v1 v2)))
  (define (add-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))
      (make-poly (variable p1)
                 (add-terms (term-list p1)
                            (term-list p2)))
      (error "Polys not in same var -- ADD-POLY"
             (list p1 p2))))
  (define (mul-poly p1 p2)
    (if (same-variable? (variable p1) (variable p2))(make-poly (variable p1)
                                                               (mul-terms (term-list p1)
                                                                          (term-list p2)))
      (error "Polys not in same var -- MUL-POLY"
             (list p1 p2))))
  (define (tag p) (attach-tag 'polynomial p))
  (put 'add '(polynomial polynomial)
       (lambda (p1 p2) (tag (add-poly p1 p2))))
  (put 'mul '(polynomial polynomial)
       (lambda (p1 p2) (tag (mul-poly p1 p2))))
  (put 'make 'polynomial
       (lambda (var terms) (tag (make-poly var terms))))
  (define (zero?-poly p)
    (every (lambda (c) (= 0 c))
           (map coeff (term-list p)))) 
  (put 'zero? '(polynomial)
        zero?-poly)
  ; now we can begin
  (define (opposite-term term)
    (make-term (order term)
               (- 0 (coeff term))))
  (define (opposite-poly p)
      (make-poly (variable p)
                 (term-list-map opposite-term (term-list p))))
  (define (sub-poly p1 p2)
    (add-poly p1
              (opposite-poly p2)))
  (put 'opposite '(polynomial)
       (lambda (p1) (tag (opposite-poly p1))))
  (put 'sub '(polynomial polynomial)
       (lambda (p1 p2) (tag (sub-poly p1 p2))))
  'done)
(install-polynomial-package)

(define (install-number-package)
  (put 'zero? '(number)
    (lambda (x) (= 0 x)))
  (put 'add '(number number)
    (lambda (a b) (+ a b))))
(install-number-package)

; generic operations
(define (=zero? exp)
  (apply-generic 'zero? exp))
(define (add a b)
  (apply-generic 'add a b))
(define (opposite a)
  (apply-generic 'opposite a))
(define (sub a b)
  (apply-generic 'sub a b))
(define (make-polynomial var terms)
  ((get 'make 'polynomial) var terms))

; examples
(define line
  (make-polynomial 'x
                   (make-term-list (list (make-term 2 1)
                                         (make-term 0 2)))))

; default term list is sparse
(define cubic
  (make-polynomial 'x
                   (make-term-list (list (make-term 3 1)
                                         (make-term 0 10)))))
(define cubic-dense
  (make-polynomial 'x
                   (make-term-list-dense (list (make-term 3 1)
                                               (make-term 0 10)))))

(define sample-term-list-sparse (cadr (cadr cubic)))
(define sample-term-list-dense (cadr (cadr cubic-dense)))

;(newline)
;(display (sub cubic line))
;(newline)
