; everything from 4.3
(define *operation-table* (make-hash-table))
(define (put op proc)
  (hash-table/put! 
    *operation-table* 
    op 
    proc))
(define (get op)
  (hash-table/get 
    *operation-table* 
    op
    #f))
(define (true? exp)
  (eq? exp true))
(define (eval-if exp env)
  (if (true? (eval (if-predicate exp) env))
    (eval (if-consequent exp) env)
    (eval (if-alternative exp) env)))
(define (if? exp) (tagged-list? exp 'if))
(define (if-predicate exp) (cadr exp))
(define (if-consequent exp) (caddr exp))
(define (if-alternative exp)
  (if (not (null? (cdddr exp)))
    (cadddr exp)
    'false))
(define (self-evaluating? exp)
  (cond ((number? exp) #t)
        ((string? exp) #t)
        ((boolean? exp) #t)
        (else false)))
(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #f))
(define (tagged-list-any? exp)
  (if (pair? exp)
      (symbol? (car exp))
      #f))
(define (eval exp env)
  (cond ((tagged-list-any? exp)
         (apply
           (get (car exp))
           (list exp env)))
        ((self-evaluating? exp) exp)
        (else
          (error "Unknown expression type -- EVAL" exp))))
(put 'if eval-if)
; exercise
(define (false? value)
  (not (true? value)))
(define (eval-and exp env)
  (define (short-circuit-and exps env)
    (if (null? exps)
        true
        (let ((current (eval (car exps) env)))
          (if (false? current)
              false
              (short-circuit-and (cdr exps) env)))))
  (short-circuit-and (cdr exp) env))
(put 'and eval-and)
(define (eval-or exp env)
  (define (short-circuit-or exps env)
    (if (null? exps)
        false
        (let ((current (eval (car exps) env)))
          (if (true? current)
              true
              (short-circuit-or (cdr exps) env)))))
  (short-circuit-or (cdr exp) env))
(put 'or eval-or)
(define (dump value)
  (display value)
  (newline))
(dump (eval '(if (and) "ok" "ko") 'some-env))
(dump (eval '(if (and #t) "ok" "ko") 'some-env))
(dump (eval '(if (and #t #t) "ok" "ko") 'some-env))
(dump (eval '(if (and #t #t #t) "ok" "ko") 'some-env))
(dump (eval '(if (and #t #t #f) "ko" "ok") 'some-env))
(dump (eval '(if (and #t #f) "ko" "ok") 'some-env))
(dump (eval '(if (and #t #f #t) "ko" "ok") 'some-env))
(dump (eval '(if (and #f) "ko" "ok") 'some-env))
(dump (eval '(if (or) "ko" "ok") 'some-env))
(dump (eval '(if (or #t) "ok" "ko") 'some-env))
(dump (eval '(if (or #f) "ko" "ok") 'some-env))
(dump (eval '(if (or #t #f) "ok" "ko") 'some-env))
(dump (eval '(if (or #t #f #t) "ok" "ko") 'some-env))
(dump (eval '(if (or #f #f) "ko" "ok") 'some-env))
(dump (eval '(if (or #f #f #f) "ko" "ok") 'some-env))
(dump (eval '(if (or #f #f #f #t) "ok" "ko") 'some-env))