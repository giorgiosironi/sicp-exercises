; library, not provided by the book once more...
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
; stuff from previous parts
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
; exercise, just implementing literals and if
(define (eval exp env)
  (cond ((tagged-list-any? exp)
         (apply
           (get (car exp))
           (list exp env)))
        ((self-evaluating? exp) exp)
        (else
          (error "Unknown expression type -- EVAL" exp))))
(put 'if eval-if)
; testing it out
(display (eval '(if #t 42 23) 'some-env))
(newline)
(display (eval '(if #f 42 23) 'some-env))
(newline)
