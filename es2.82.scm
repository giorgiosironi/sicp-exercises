; http://eli.thegreenplace.net/2007/09/16/sicp-section-252
; these primitives were not present in my version of Scheme
; and it is unacceptable to write code without being able to run it
(define *coercion-table* (make-hash-table))
(define (put-coercion type-from type-to proc)
    (hash-table/put! 
          *coercion-table* 
              (list type-from type-to) 
                  proc))
(define (get-coercion type-from type-to)
    (hash-table/get 
          *coercion-table* 
              (list type-from type-to) 
                  #f))
;' extending it myself because we're missing also put and get
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
; current exercise
(define (apply-generic op . args)
  (bkpt 'apply-generic args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (if (= (length args) 2)
          (let ((type1 (car type-tags))
                (type2 (cadr type-tags))
                (a1 (car args))
                (a2 (cadr args)))
            (try-coercion op args type-tags type-tags)))))))
(define (try-coercion op args type-tags types-to-try)
  (if (= 0
         (length types-to-try))
      (error "Cannot coerce to any of the types" (list op args type-tags))
      (let ((target-type (car types-to-try)))
          (let ((coercions (map 
                             (lambda (ti) (get-coercion ti target-type))
                             type-tags)))
            (if (every (lambda (coercion) (not (eq? #f coercion)))
                       coercions)
                (apply apply-generic
                       (append (list op)
                               (coerce coercions args)))
                (try-coercion op args type-tags (cdr types-to-try)))))))

(define (coerce coercions args)
  (if (= 0
         (length args))
      args
      (cons (apply (car coercions)
                   (list (car args)))
            (coerce (cdr coercions)
                    (cdr args)))))

; testing type hierarchy, not the transformation
(define (type-tag pair) (car pair))
(define (contents pair) (cadr pair))
; identites only because there is a single representation for simplicity of thistest
(define (to type)
  (lambda (original)
    (list type (contents original))))
(put-coercion 'natural 'scheme-number (to 'scheme-number))
(put-coercion 'scheme-number 'rational (to 'rational))
(define (identity x) x)
; natural identities
(put-coercion 'natural 'natural identity)
(put-coercion 'scheme-number 'scheme-number identity)
(put-coercion 'rational 'rational identity)
(put 'exp '(rational rational) (lambda (a b) (expt a b)))

