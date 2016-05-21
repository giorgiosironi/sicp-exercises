; library
(define (enclosing-environment env) (cdr env))
(define (first-frame env) (car env))
(define the-empty-environment '())
(define (make-frame variables values)
  (cons variables values))
(define (frame-variables frame) (car frame))
(define (frame-values frame) (cdr frame))
(define (add-binding-to-frame! var val frame)
  (set-car! frame (cons var (car frame)))
  (set-cdr! frame (cons val (cdr frame))))
(define (extend-environment vars vals base-env)
  (if (= (length vars) (length vals))
    (cons (make-frame vars vals) base-env)
    (if (< (length vars) (length vals))
      (error "Too many arguments supplied" vars vals)
      (error "Too few arguments supplied" vars vals))))
(define (scan vars vals var on-found on-not-found)
  (cond ((null? vars)
         (on-not-found))
        ((eq? var (car vars))
         (on-found vars vals))
        (else (scan (cdr vars) (cdr vals) var on-found on-not-found))))
; TODO: extract env-loop
(define (env-loop env on-frame)
  (if (eq? env the-empty-environment)
    (error "Reached the empty environment")
    (let ((frame (first-frame env)))
      (on-frame (first-frame env)
                (lambda () (env-loop (enclosing-environment env)
                                     on-frame))))))
(define (lookup-variable-value var env)
  (env-loop env
            (lambda (frame continue)
              (scan (frame-variables frame)
                    (frame-values frame)
                    var
                    (lambda (vars vals) (car vals))
                    continue))))
(define (set-variable-value! var val env)
  (env-loop env
            (lambda (frame continue)
              (scan (frame-variables frame)
                    (frame-values frame)
                    var
                    (lambda (vars vals) (set-car! vals val))
                    continue))))
(define (define-variable! var val env)
  (let ((frame (first-frame env)))
    (scan (frame-variables frame)
          (frame-values frame)
          var
          (lambda (vars vals) (set-car! vals val))
          (lambda () (add-binding-to-frame! var val frame)))))
; exercise
; completing the specification: we only remove the binding from the most specific environment where we find it, as:
; - it's the most conservative operation (you can repeat it if you want to remove it also from parent environments)
; - removing it from the parent is dangerous as it may affect other environments which descend from the same parent
(define (make-unbound! var env)
  (let ((frame (first-frame env)))
    (scan (frame-variables frame)
          (frame-values frame)
          var
          (lambda (vars vals) 
            (set-car! vals (cdr vals))
            (set-car! vars (cdr vars)))
          (lambda () (error "Variable not found -- MAKE-UNBOUND!" var)))))
; tests
; should be 64
(define father-env (extend-environment '(a b c) '(32 42 64) the-empty-environment))
(define child-env (extend-environment '(c d) '(128 256) father-env))
(make-unbound! 'c child-env)
(display (lookup-variable-value 'c child-env))
(newline)
