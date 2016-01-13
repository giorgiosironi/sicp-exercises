(load "chapter5.4.scm")
(load "es4.5.scm")

(add-operation 'cond?
               (lambda (exp) (tagged-list? exp 'cond)))
(define (cond-first-clause exp)
  (car (cdr exp)))
(define (cond-rest-clauses exp)
  (cdr (cdr exp)))
(add-operation 'cond-first-predicate
               (lambda (exp) (car (cond-first-clause exp))))
(add-operation 'cond-first-sequence
               (lambda (exp) (cdr (cond-first-clause exp))))
(add-operation 'cond-remove-first-clause
               (lambda (exp) (cons 'cond (cond-rest-clauses exp))))
(apply-patch '(cond-if-patch-start
               (test (op cond?) (reg exp))
               ; implement cond, this is copied by if
               (branch (label ev-cond))
               (goto (label cond-if-patch-end))
    ev-cond
    (save exp) ; save expression for later
    (save env)
    (save continue)
    (assign continue (label ev-cond-first-decide))
    (assign exp (op cond-first-predicate) (reg exp))
    (goto (label eval-dispatch)) ; evaluate the predicate
    ev-cond-first-decide
    (restore continue)
    (restore env)
    (restore exp)
    (test (op true?) (reg val))
    (branch (label ev-cond-first-sequence))
    ev-if-alternative ; here recur on the rest of the cond
    (assign exp (op cond-remove-first-clause) (reg exp))
    (goto (label eval-dispatch))
    ev-cond-first-sequence ; body of the cond
    (assign unev (op cond-first-sequence) (reg exp))
    (save continue) ; action at a distance since ev-sequence will restore it
    (goto (label ev-sequence))
              cond-if-patch-end)
             'extensions)

(start eceval)

