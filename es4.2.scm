; a. Cannot put the application clause at the top because it is just (pair? exp)
; and hence all the other definitions (being tagged lists of the form '(tag ...)
; will satisfy it
; b. Changing the syntax of applications using call means rewriting the related primitives so that they accept (call + 1 2)
; library...
(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #f))
; these change:
(define (application? exp) (tagged-list? exp 'call))
(define (operator exp) (cadr exp))
(define (operands exp) (cddr exp))
; no changes for:
(define (no-operands? ops) (null? ops))
(define (first-operand ops) (car ops))
(define (rest-operands ops) (cdr ops))
