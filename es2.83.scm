;' operation table
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
; simplified apply-generic for this exercise 
(define (type-tag pair) (car pair))
(define (contents pair) (cadr pair))
(define (tag type contents) (list type contents))
(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (error "Cannot find procedure for these types -- APPLY-GENERIC" list (op type-tags))))))
; exercise: integer to rational
(define (raise-integer->rational integer)
  (cons integer 1))
(put 'raise '(integer)
  (lambda (integer) (tag 'rational (raise-integer->rational integer))))
; exercise: rational to real
(define (raise-rational->real rational)
  (/ (car rational) (cdr rational)))
(put 'raise '(rational)
  (lambda (rational) (tag 'real (raise-rational->real rational))))
; exercise: real to complex
(define (raise-real->complex real)
  (list real 0))
(put 'raise '(real)
  (lambda (real) (tag 'complex (raise-real->complex real))))
