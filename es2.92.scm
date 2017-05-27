; library from previous exercises (2.87)
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
(define (type-tag pair) (car pair))
(define (contents pair) (cadr pair))
(define (attach-tag tag contents) (list tag contents))
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (error "Cannot find procedure for these types -- APPLY-GENERIC" list (op type-tags))))))
(define (adjoin-term term term-list)
  (if (=zero? (coeff term))
    term-list
    (cons term term-list)))
(define (the-empty-termlist) '())
(define (first-term term-list) (car term-list))
(define (rest-terms term-list) (cdr term-list))
(define (empty-termlist? term-list) (null? term-list))
(define (make-term order coeff) (list order coeff))
(define (order term) (car term))
(define (coeff term) (cadr term))
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
(define (install-polynomial-package)
  ;; internal procedures
  ;; representation of poly
  (define (make-poly variable term-list)
    (cons variable term-list))
  (define (variable p) (car p))
  (define (term-list p) (cdr p))
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
  ; ok, now we can begin...
  (define (zero?-poly p)
    (every (lambda (c) (= 0 c))
           (map coeff (term-list p)))) 
  (put 'zero? '(polynomial)
        zero?-poly)
  'done)
(install-polynomial-package)
(define (install-number-package)
  (put 'zero? '(number)
    (lambda (x) (= 0 x)))
  (put 'add '(number number)
    (lambda (a b) (+ a b))))
(install-number-package)
(define (make-polynomial var terms)
  ((get 'make 'polynomial) var terms))
(define (add a b)
  (apply-generic 'add a b))
(define (=zero? exp)
  (apply-generic 'zero? exp))
; conversion
(define (convert variable p)
  ; simple assumption: no presence of variable in terms TODO: extend
  (make-polynomial variable
                   (list (make-term 0 p))))
; samples
(define sample-only-x-polynomial ; x^2 + x
  (make-polynomial 'x
                   (list (make-term 2 (attach-tag 'number 1))
                         (make-term 1 (attach-tag 'number 1)))))
(define sample-only-y-polynomial ; y^3 + 4
  (make-polynomial 'y
                   (list (make-term 3 (attach-tag 'number 1))
                         (make-term 0 (attach-tag 'number 4)))))
(define sample-y-with-x-polynomial ; xy^3
  (make-polynomial 'y
                   (list (make-term 3 (make-polynomial 'x (list (make-term 1 1)))))))
; TODO: automated conversion from x to y polynomial
(display (add sample-only-x-polynomial (convert 'x sample-only-y-polynomial)))
(newline)
; TODO: more samples
(display (add sample-only-x-polynomial (convert 'x sample-y-with-x-polynomial)))
(newline)
(load "/code/test-manager/load.scm")
(in-test-group
   addition
   (define-each-test
     (check (equal? 
              '(polynomial (x (2 (number 1))
                              (1 (number 1))
                              (0 (polynomial (y (3 (number 1))
                                                (0 (number 4)))))))
              (add sample-only-x-polynomial (convert 'x sample-only-y-polynomial)))
              "Addition of two polynomials with different vars but integer coefficients")

     (check (equal? 
              '(polynomial (x (2 (number 1))
                              (1 (polynomial (y (3 (number 1))
                                                (0 (number 1)))))))
              (add sample-only-x-polynomial (convert 'x sample-y-with-x-polynomial)))
              "Addition where one polynomial has a polynomial coefficient")
     ))
; TODO: multiplication
(run-registered-tests)
