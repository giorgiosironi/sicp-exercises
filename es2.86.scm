; choosing the cartesian representation
(define (make-complex-cartesian a b)
  (list a b))
(define (make-complex-polar ro tau)
  (let ((a (apply-generic 'times
                          ro
                          (apply-generic 'cosine tau)))
        (b (apply-generic 'times
                          ro
                          (apply-generic 'sine tau))))
    (make-complex-cartesian a
                            b)))
; previously on SICP: infrastructure stuff the book does not provide
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
(define (make-rat n d) (list n d))
(define (numer r) (car r))
(define (denom r) (cadr r))
; the simplest version because it's orthogonal to these new implementations
(define (apply-generic op . args)
  (display op)
  (newline)
  (display args)
  (newline)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (error "Cannot find procedure for these types -- APPLY-GENERIC" list (op type-tags))))))
; defining times
(put 'times
     '(real real)
     (lambda (a b)
       (tag 'real (* a b))))
(put 'times
     '(rational rational)
     (lambda (a b)
       (tag 'rational (make-rat (* (numer a)
                                   (numer b))
                                (* (denom a)
                                   (denom b))))))
