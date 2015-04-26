(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (if (= (length args) 2)
          (let ((type1 (car type-tags))
                (type2 (cadr type-tags))
                (a1 (car args))
                (a2 (cadr args)))
            (try-coercion op args type-tags types-tags)))))))
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
                (apply 'apply-generic
                       (list op
                             (coerce coercions args)))
                (try-coercion op args type-tags (cdr types-to-try)))))))

(define (coerce coercions args)
  (if (= 0
         (length args)
         args)
      (cons (apply (car coercions)
                   (list (car args)))
            (coerce (cdr coercions)
                    (cdr args)))))
