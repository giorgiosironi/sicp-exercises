;' previously on SICP: operation table
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
; previously on SICP: primitives 
(define (type-tag pair) (car pair))
(define (contents pair) (cadr pair))
(define (tag type contents) (list type contents))
; previously on SICP: raising
(define (raise-integer->rational integer)
  (list integer 1))
(put 'raise '(integer)
  (lambda (integer) (tag 'rational (raise-integer->rational integer))))
(define (raise-rational->real rational)
  (/ (car rational) (cadr rational)))
(put 'raise '(rational)
  (lambda (rational) (tag 'real (raise-rational->real rational))))
(define (raise-real->complex real)
  (list real 0))
(put 'raise '(real)
  (lambda (real) (tag 'complex (raise-real->complex real))))
; previously on SICP: helpers for apply-generic
(define types '(complex real rational integer))
(define (higher first-type second-type)
  (define (stop-at-first first-type second-type remaining-types)
    (let ((highest (car remaining-types)))
      (cond ((eq? highest first-type)
             first-type)
            ((eq? highest second-type)
             second-type)
            (else
             (stop-at-first first-type 
                            second-type
                            (cdr remaining-types))))))
  (stop-at-first first-type second-type types))
(define (highest types)
  (reduce higher
          (car types)
          types))
(define (raise-all-to type args)
  (map (lambda (arg) (raise-to type arg))
       args))
(define (raise-to type arg)
  (if (eq? type
           (type-tag arg))
      arg
      (raise-to type (apply-generic 'raise arg))))
; previously on SICP: summing complex numbers
(define (make-complex r i)
  (list r i))
(define (real-part complex)
  (car complex))
(define (imag-part complex)
  (cadr complex))
(define (sum-complex . args)
  (reduce (lambda (a b)
            (make-complex (+ (real-part a)
                             (real-part b))
                          (+ (imag-part a)
                             (imag-part b))))
          (car args)
          args))
(put 'sum
     '(complex complex)
     (lambda (a b) (tag 'complex (sum-complex a b))))
; TODO: implement project
(define (project-rational rational)
  (floor->exact (/ (car rational) (cadr rational))))
(put 'project '(rational)
  (lambda (rational) (tag 'integer (project-rational rational))))
(define (project-real real)
  (let ((denominator 10000))
    (list (floor->exact (* real denominator))
          denominator)))
(put 'project '(real)
  (lambda (real) (tag 'rational (project-real real))))
(define (project-complex complex)
  (real-part complex))
(put 'project '(complex)
  (lambda (complex) (tag 'real (project-complex complex))))
; TODO: implement equal
; TODO: implement drop
; apply-generic (will be modified to use drop)
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (let ((highest-type (highest type-tags)))
          (apply apply-generic
                 (append (list op)
                         (raise-all-to highest-type args))))))))
