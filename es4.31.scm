; I can never run this code because it depends on half of the book, forgive me
; application does not change as the actual-value of the operand is still needed
; and operands will be treated elsewhere
((application? exp)
 (apply (actual-value (operator exp) env)
        (operands exp)
        env))
; here force-it does all the work
(define (actual-value exp env)
  (force-it (eval exp env)))
; I'm assuming our changes only applied to compound procedures
(define (apply procedure arguments env)
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure
           procedure
           (list-of-arg-values arguments env))) ; changed
        ((compound-procedure? procedure)
         (eval-sequence
           (procedure-body procedure)
           (extend-environment
             (procedure-parameters procedure)
             (list-of-delayed-args arguments 
                                   ; procedure does have to maintain a list of the modes of its parameters, not just parameters and body
                                   (procedure-parameters-modes procedure)
                                   env) ; changed
             (procedure-environment procedure))))
        (else
          (error
            "Unknown procedure type -- APPLY" procedure))))
; so how an argument is evaluated depends on the define
; and never on the actual procedure call... this is a shockingly bad idea
; as you never know what a call does when you see it, you have to know
(define (list-of-delayed-args exps modes env)
  (if (no-operands? exps)
    '()
    (cons (delay-it-if-necessary (first-operand exps) (car modes) env)
          (list-of-delayed-args (rest-operands exps)
                                (cdr modes)
                                env))))
; force-it has to incorporate both the memoized and not-memoized cases
(define (force-it obj)
  (cond ((thunk? obj)
         (actual-value (thunk-exp obj) (thunk-env obj)))
        ((memo-thunk? obj)
         (let ((result (actual-value
                         (thunk-exp obj)
                         (thunk-env obj))))
           (set-car! obj 'evaluated-thunk)
           (set-car! (cdr obj) result) 
           (set-cdr! (cdr obj) '()) result))
        ((evaluated-thunk? obj)
         (thunk-value obj))
        (else obj)))
; delay tags differently the expression depending on whether it is to be memoized or not
; also, it may not even tag it as it's not to be delayed at all
(define (delay-it-if-necessary exp mode env)
  (cond ((eq? mode 'lazy)
         (list 'thunk exp env))
        ((eq? mode 'lazy-memo)
         (list 'memo-thunk exp env))
        (else exp)))
