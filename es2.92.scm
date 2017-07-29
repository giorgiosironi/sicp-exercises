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
(define (type-tag pair) 
  (if (pair? pair)
    (car pair)
    (error "Not a pair -- TYPE-TAG" pair)))
(define (contents pair) (cadr pair))
(define (attach-tag tag contents) (list tag contents))
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (error "Cannot find procedure for these types -- APPLY-GENERIC" (list op type-tags))))))
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
  (define (simplify var terms)
    ; simplifications: if it's coeff*x^0, it's just coeff
    (cond
      ((and (eq? (length terms) 1)
            (eq? (order (first-term terms)) 0))
       (coeff (first-term terms)))
      ((eq? (length terms) 0)
       (make-number 0))
      (else (make-polynomial var terms))))
  (define (convert p)
    (let ((original-var (variable p)))
      (lambda (v)
        (if (eq? (type-tag p) 'number)
          ; no need to convert a number, it's pure
          p
          (if (eq? (the-empty-termlist) (term-list p))
            (make-polynomial v (the-empty-termlist))
            (let ((original-c (coeff (first-term (term-list p))))
                  (original-o (order (first-term (term-list p))))
                  (rest-of-p (make-poly original-var (rest-terms (term-list p))))) 
              (let ((converted-first-term
                      (if (and (eq? (type-tag original-c) 'polynomial)
                               (same-variable? (variable (contents original-c))
                                               v))
                        (let ((new-o (order (first-term (term-list (contents original-c)))))
                              (new-c (coeff (first-term (term-list (contents original-c))))))
                          (make-polynomial v (list (make-term new-o
                                                       (simplify original-var
                                                                        (list (make-term original-o new-c)))))))
                        (make-polynomial v
                                  (list (make-term 0 (simplify original-var (list (first-term (term-list p)))))))))
                    (converted-rest-of-p ((convert rest-of-p) v)))
                ;(display "converted-first-term ")
                ;(display converted-first-term)
                ;(newline)
                ;(display "rest-of-p ")
                ;(display rest-of-p)
                ;(newline)
                ;(display "convert rest-of-p ")
                ;(display converted-rest-of-p)
                ;(newline)
                (add converted-first-term converted-rest-of-p))))))))
  (define (add-poly-number p n)
    (let ((p-with-coalesced-0th-term
            (if (any (lambda (term) (eq? (order term) 0))
                     (term-list p))
              p
              (make-poly (variable p)
                         (append (term-list p) 
                                 (list (make-term 0 (list 'number 0))))))))

      (make-poly (variable p-with-coalesced-0th-term)
                 (map (lambda (term)
                        (if (eq? (order term) 0)
                          (make-term (order term) (add (coeff term) (attach-tag 'number n)))
                          term))
                      (term-list p-with-coalesced-0th-term)))))
  (put 'add '(polynomial polynomial)
       (lambda (p1 p2) (tag (add-poly p1 p2))))
  (put 'add '(polynomial number)
       (lambda (p1 p2) (tag (add-poly-number p1 p2))))
  (put 'add '(number polynomial)
       (lambda (p1 p2) (tag (add-poly-number p2 p1))))
  (put 'mul '(polynomial polynomial)
       (lambda (p1 p2) (tag (mul-poly p1 p2))))
  (put 'make 'polynomial
       (lambda (var terms) 
          (cond
            (else (tag (make-poly var terms))))))
  ; ok, now we can begin...
  (define (zero?-poly p)
    ; TODO: this should be made generic too
    (every (lambda (c) (or (eq? 0 c) (eq? '(number 0) c)))
           (map coeff (term-list p)))) 
  (put 'zero? '(polynomial)
        zero?-poly)
  (put 'convert '(polynomial)
        convert)
  'done)
(install-polynomial-package)
(define (install-number-package)
  (put 'zero? '(number)
    (lambda (x) (= 0 x)))
  (put 'add '(number number)
    (lambda (a b) (attach-tag 'number (+ a b))))
  (put 'make 'number
    (lambda (n) (attach-tag 'number n))))
(install-number-package)
(define (poly? exp)
  (eq? 'polynomial (type-tag exp)))
(define (make-polynomial var terms)
  ((get 'make 'polynomial) var terms))
(define (make-number n)
  ((get 'make 'number) n))
(define (add a b)
  (let ((result (apply-generic 'add a b)))
    (display "add: ")
    (newline)
    (display a)
    (newline)
    (display b)
    (newline)
    (display "result: ")
    (newline)
    (display result)
    (newline)
    result))
(define (=zero? exp)
  (apply-generic 'zero? exp))
; conversion
(define (convert variable p)
  ((apply-generic 'convert p) variable))
; samples
(define zero-x
  (make-polynomial 'x
                   (list)))
(define zero-y
  (make-polynomial 'y
                   (list)))
(define x
  (make-polynomial 'x
                   (list (make-term 1 (make-number 1)))))
(define y
  (make-polynomial 'y
                   (list (make-term 1 (make-number 1)))))
(define x+1
  (make-polynomial 'x
                   (list (make-term 1 (make-number 1))
                         (make-term 0 (make-number 1)))))
(define x+3
  (make-polynomial 'x
                   (list (make-term 1 (make-number 1))
                         (make-term 0 (make-number 3)))))
(define poly-2x
  (make-polynomial 'x
                   (list (make-term 1 (make-number 2)))))
(define poly-2x+3
  (make-polynomial 'x
                   (list (make-term 1 (make-number 2))
                         (make-term 0 (make-number 3)))))
(define x+y
  (make-polynomial 'x
                   (list (make-term 1 (make-number 1))
                         (make-term 0 y))))
(define y+3
  (make-polynomial 'y
                   (list (make-term 1 (make-number 1))
                         (make-term 0 (make-number 3)))))
(define x+y+3
  (make-polynomial 'x
                   (list (make-term 1 (make-number 1))
                         (make-term 0 y+3))))
(define x^2+x
  (make-polynomial 'x
                   (list (make-term 2 (make-number 1))
                         (make-term 1 (make-number 1)))))
(define y^3+4 ; y^3 + 4
  (make-polynomial 'y
                   (list (make-term 3 (make-number 1))
                         (make-term 0 (make-number 4)))))
(define xy^3
  (make-polynomial 'y
                   (list (make-term 3 (make-polynomial 'x (list (make-term 1 (make-number 1))))))))
(define y^3x 
  (make-polynomial 'x
                   (list (make-term 1 (make-polynomial 'y (list (make-term 3 (make-number 1))))))))
(define 4xy^3
  (make-polynomial 'y
                   (list (make-term 3 (make-polynomial 'x (list (make-term 1 (make-number 4))))))))
(define 4y^3x
  (make-polynomial 'x
                   (list (make-term 1 (make-polynomial 'y (list (make-term 3 (make-number 4))))))))
(define xy^2+1
  (make-polynomial 'y
                   (list (make-term 2 (make-polynomial 'x (list (make-term 1 (make-number 1)))))
                         (make-term 0 (make-number 1)))))
(define y^2x+1
  (make-polynomial 'x
                   (list (make-term 1 (make-polynomial 'y (list (make-term 2 (make-number 1)))))
                         (make-term 0 (make-number 1)))))
; TODO: automated conversion from x to y polynomial
(load "/code/test-manager/load.scm")
(in-test-group
   conversion ;-to-a-different-variable
   (define-each-test
     (check (equal? 
              zero-x
              (convert 'x zero-y))
              "Conversion of empty polynomial")

     (check (equal? 
              y^3x
              (convert 'x xy^3))
              "Conversion of polynomial with y terms multiplied by some x, one term")

     (check (equal? 
              4y^3x
              (convert 'x 4xy^3))
              "Conversion of polynomial with y terms multiplied by some x, one term that has a coefficient")

     (check (equal? 
              (list 'polynomial (list 'x (list 0 y^3+4)))
              (convert 'x y^3+4))
              "Conversion of polynomial with constant y terms")

     (check (equal? 
              y^2x+1
              (convert 'x xy^2+1))
              "Conversion of polynomial with y terms multiplied by some x, one term that has a coefficient")
     ))
(in-test-group
   addition
   (define-each-test
     (check (equal? 
              x+3
              (add x+1 '(number 2)))
              "Addition of a polynomial with a 0th term and a number")
     (check (equal? 
              x+3
              (add x '(number 3)))
              "Addition of a polynomial without a 0th term and a number")
     (check (equal? 
              poly-2x+3
              (add poly-2x '(number 3)))
              "Addition of a polynomial without a 0th term but with a coefficient and a number")
     (check (equal? 
              x+y
              (add x (convert 'x y)))
              "Addition of a polynomial without a 0th term but with a coefficient and a number")
     (check (equal? 
              x+y+3
              (add x+3 (convert 'x y)))
              "Addition of two polynomials with 0th terms")
     ;(check (equal? 
     ;         '(polynomial (x (2 (number 1))
     ;                         (1 (number 1))
     ;                         (0 (polynomial (y (3 (number 1))
     ;                                           (0 (number 4)))))))
     ;         (add x^2+x (convert 'x y^3+4)))
     ;         "Addition of two polynomials with different vars but integer coefficients")

     ;(check (equal? 
     ;         '(polynomial (x (2 (number 1))
     ;                         (1 (polynomial (y (3 (number 1))
     ;                                           (0 (number 1)))))))
     ;         (add x^2+x (convert 'x xy^3)))
     ;         "Addition where one polynomial has a polynomial coefficient")
     ))
; TODO: multiplication
(run-registered-tests)
;(run-test '(conversion anonymous-test-4))
;(run-test '(addition anonymous-test-8))
