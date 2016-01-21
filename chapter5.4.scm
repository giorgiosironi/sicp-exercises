(load "es4.5.scm")
(load "es4.13.scm")
(load "es4.22.scm")
(load "chapter5.2.scm")
(define explicit-control-evaluator '(
    read-eval-print-loop
    (perform (op initialize-stack))
    (perform (op prompt-for-input) (const ";;; EC-Eval input:"))
    (assign exp (op read))
    (assign env (op get-global-environment))
    (assign continue (label print-result))
    (goto (label eval-dispatch))
    ; eval starts with a case analysis on the type of the expression
    eval-dispatch
    (test (op self-evaluating?) (reg exp))
    (branch (label ev-self-eval))
    (test (op variable?) (reg exp))
    (branch (label ev-variable))
    (test (op quoted?) (reg exp))
    (branch (label ev-quoted))
    (test (op assignment?) (reg exp))
    (branch (label ev-assignment))
    (test (op definition?) (reg exp))
    (branch (label ev-definition))
    (test (op if?) (reg exp))
    (branch (label ev-if))
    (test (op lambda?) (reg exp))
    (branch (label ev-lambda))
    (test (op begin?) (reg exp))
    (branch (label ev-begin))
    ; label to target for patching in derived expressions
    extensions
    (test (op application?) (reg exp))
    (branch (label ev-application))
    (goto (label unknown-expression-type))
    ; evaluating simple expressions
    ev-self-eval
    (assign val (reg exp))
    (goto (reg continue))
    ev-variable
    (assign val (op lookup-variable-value) (reg exp) (reg env))
    (goto (reg continue))
    ev-quoted
    (assign val (op text-of-quotation) (reg exp))
    (goto (reg continue))
    ev-lambda
    (assign unev (op lambda-parameters) (reg exp))
    (assign exp (op lambda-body) (reg exp))
    (assign val (op make-procedure) (reg unev) (reg exp) (reg env))
    (goto (reg continue))
    ; evaluating procedure applications
    ;; evaluating operator
    ev-application
    (save continue)
    (save env)
    (assign unev (op operands) (reg exp))
    (save unev)
    (assign exp (op operator) (reg exp))
    (assign continue (label ev-appl-did-operator))
    (goto (label eval-dispatch))
    ;; evaluating operands
    ev-appl-did-operator
    (restore unev) ; the operands
    (restore env)
    (assign argl (op empty-arglist))
    (assign proc (reg val)) ; the operator
    (test (op no-operands?) (reg unev))
    (branch (label apply-dispatch))
    (save proc)
    ; cycle of the argument-evaluation loop
    ev-appl-operand-loop
    (save argl)
    (assign exp (op first-operand) (reg unev))
    (test (op last-operand?) (reg unev))
    (branch (label ev-appl-last-arg))
    (save env)
    (save unev)
    (assign continue (label ev-appl-accumulate-arg))
    (goto (label eval-dispatch))
    ; when an operand has been evaluated, we put in in argl
    ; and continue to evaluate the others from unev
    ev-appl-accumulate-arg
    (restore unev)
    (restore env)
    (restore argl)
    (assign argl (op adjoin-arg) (reg val) (reg argl))
    (assign unev (op rest-operands) (reg unev))
    (goto (label ev-appl-operand-loop))
    ; the last argument evaluation is different:
    ; we need to dispatch on proc
    ev-appl-last-arg
    (assign continue (label ev-appl-accum-last-arg))
    (goto (label eval-dispatch))
    ev-appl-accum-last-arg
    (restore argl)
    (assign argl (op adjoin-arg) (reg val) (reg argl))
    (restore proc)
    (goto (label apply-dispatch))
    ; apply procedure of the metacircular evaluator:
    ; choose between primitive or user-defined procedure
    apply-dispatch
    (test (op primitive-procedure?) (reg proc))
    (branch (label primitive-apply))
    (test (op compound-procedure?) (reg proc))
    (branch (label compound-apply))
    (goto (label unknown-procedure-type))
    ; let's apply a primitive operator such as +
    primitive-apply
    (assign val (op apply-primitive-procedure) (reg proc) (reg argl))
    (restore continue)
    (goto (reg continue))
    ; let's apply a compound procedure like a user-defined one
    compound-apply
    (assign unev (op procedure-parameters) (reg proc))
    (assign env (op procedure-environment) (reg proc))
    (assign env (op extend-environment) (reg unev) (reg argl) (reg env))
    (assign unev (op procedure-body) (reg proc))
    (goto (label ev-sequence))
    ; evaluates a sequence of expressions
    ev-begin
    (assign unev (op begin-actions) (reg exp)) ; list of unevaluated expressions
    (save continue)
    (goto (label ev-sequence))
    ;; let's go evaluate each element of the sequence
    ev-sequence
    (assign exp (op first-exp) (reg unev))
    (test (op last-exp?) (reg unev))
    (branch (label ev-sequence-last-exp))
    (save unev)
    (save env)
    (assign continue (label ev-sequence-continue))
    (goto (label eval-dispatch))
    ;; we return after having evaluated the element
    ;; there is no return value
    ev-sequence-continue
    (restore env)
    (restore unev)
    (assign unev (op rest-exps) (reg unev))
    (goto (label ev-sequence))
    ;; the last element of the sequence is handled differently
    ;; basically it substitutes the previous expression without
    ;; saving values on the stack: it's tail-recursive
    ev-sequence-last-exp
    (restore continue)
    (goto (label eval-dispatch))
    ; evaluating conditionals
    ev-if
    (save exp) ; save expression for later
    (save env)
    (save continue)
    (assign continue (label ev-if-decide))
    (assign exp (op if-predicate) (reg exp))
    (goto (label eval-dispatch)) ; evaluate the predicate
    ev-if-decide
    (restore continue)
    (restore env)
    (restore exp)
    (test (op true?) (reg val))
    (branch (label ev-if-consequent))
    ev-if-alternative ; else
    (assign exp (op if-alternative) (reg exp))
    (goto (label eval-dispatch))
    ev-if-consequent ; then
    (assign exp (op if-consequent) (reg exp))
    (goto (label eval-dispatch))
    ; assignments puts values in the environment
    ev-assignment
    (assign unev (op assignment-variable) (reg exp))
    (save unev) ; save variable for later
    (assign exp (op assignment-value) (reg exp))
    (save env)
    (save continue)
    (assign continue (label ev-assignment-1))
    (goto (label eval-dispatch)) ; evaluate the assignment value
    ev-assignment-1
    (restore continue)
    (restore env)
    (restore unev)
    (perform (op set-variable-value!) (reg unev) (reg val) (reg env))
    (assign val (const ok))
    (goto (reg continue))
    ; definitions are very similarly put into the current environment
    ev-definition
    (assign unev (op definition-variable) (reg exp))
    (save unev) ; save variable for later
    (assign exp (op definition-value) (reg exp))
    (save env)
    (save continue)
    (assign continue (label ev-definition-1))
    (goto (label eval-dispatch)) ; evaluate the definition value
    ev-definition-1
    (restore continue)
    (restore env)
    (restore unev)
    (perform (op define-variable!) (reg unev) (reg val) (reg env))
    (assign val (const ok))
    (goto (reg continue))
    print-result
    (perform (op announce-output) (const ";;; EC-Eval value:"))
    (perform (op user-print) (reg val))
    (goto (label read-eval-print-loop))
    unknown-expression-type
    (assign val (const unknown-expression-type-error))
    (goto (label signal-error))
    unknown-procedure-type
    (restore continue) ; clean up stack (from apply-dispatch)
    (assign val (const unknown-procedure-type-error))
    (goto (label signal-error))
    signal-error
    (perform (op user-print) (reg val))
    (goto (label read-eval-print-loop))
    ))
(define (self-evaluating? exp)
  (cond ((number? exp) true)
        ((string? exp) true)
        (else false)))
(define (variable? exp) (symbol? exp))
(define (quoted? exp)
  (tagged-list? exp 'quote))
(define (text-of-quotation exp) (cadr exp))
(define (tagged-list? exp tag)
  (if (pair? exp)
    (eq? (car exp) tag)
    false))
(define (assignment? exp)(tagged-list? exp 'set!))
(define (assignment-variable exp) (cadr exp))
(define (assignment-value exp) (caddr exp))
(define (definition? exp)
  (tagged-list? exp 'define))
(define (definition-variable exp)
  (if (symbol? (cadr exp))
    (cadr exp)
    (caadr exp)))
(define (definition-value exp)
  (if (symbol? (cadr exp))
    (caddr exp)
    (make-lambda (cdadr exp)
                 ; formal parameters
                 (cddr exp)))) ; body
(define (lambda? exp) (tagged-list? exp 'lambda))
(define (lambda-parameters exp) (cadr exp))
(define (lambda-body exp) (cddr exp))
; We also provide a constructor for lambda expressions, which is used by definition-value, above:
(define (make-lambda parameters body)
  (cons 'lambda (cons parameters body)))
(define (if? exp) (tagged-list? exp 'if))
(define (if-predicate exp) (cadr exp))
(define (if-consequent exp) (caddr exp))
(define (if-alternative exp)
  (if (not (null? (cdddr exp)))
    (cadddr exp)
    'false))
(define (make-if predicate consequent alternative)
  (list 'if predicate consequent alternative))
(define
  (begin? exp) (tagged-list? exp 'begin))
(define
  (begin-actions exp) (cdr exp))
(define
  (last-exp? seq) (null? (cdr seq)))
(define
  (first-exp seq) (car seq))
(define
  (rest-exps seq) (cdr seq))
(define (sequence->exp seq)
  (cond ((null? seq) seq)
        ((last-exp? seq) (first-exp seq))
        (else (make-begin seq))))
(define (make-begin seq) (cons 'begin seq))
(define
  (application? exp) (pair? exp))
(define
  (operator exp) (car exp))
(define
  (operands exp) (cdr exp))
(define
  (no-operands? ops) (null? ops))
(define
  (first-operand ops) (car ops))
(define
  (rest-operands ops) (cdr ops))
; from fucking footnotes
(define (empty-arglist) '())
(define (adjoin-arg arg arglist)
  (append arglist (list arg)))
; We also use an additional syntax procedure to test for the last operand in a combination:
(define (last-operand? ops)(null? (cdr ops)))
; primitive procedures
(define apply-in-underlying-scheme apply)
(define (primitive-implementation proc) (cadr proc))
(define (apply-primitive-procedure proc args)
  (apply-in-underlying-scheme
    (primitive-implementation proc) args))
; from previous chapter 4
(define (user-print object)
  (if (compound-procedure? object)
    (display (list 'compound-procedure
                   (procedure-parameters object)
                   (procedure-body object)
                   '<procedure-env>))
    (display object)))
(define input-prompt ";;; M-Eval input:")
(define output-prompt ";;; M-Eval value:")
(define (driver-loop)
  (prompt-for-input input-prompt)
  (let ((input (read)))
    (let ((output (eval input the-global-environment)))
      (announce-output output-prompt)
      (user-print output)))
  (driver-loop))
(define (prompt-for-input string)
  (newline) (newline) (display string) (newline))
(define (announce-output string)
  (newline) (display string) (newline))
; environment-related missing procedures
(define primitive-procedures
  (list (list 'car car)
        (list 'cdr cdr)
        (list 'cons cons)
        (list 'null? null?)
        (list '+ +)
        ))
(define (primitive-procedure? proc)
  (tagged-list? proc 'primitive))
(define (primitive-implementation proc) (cadr proc))
(define (primitive-procedure-names)
  (map car
       primitive-procedures))
(define (primitive-procedure-objects)
  (map (lambda (proc) (list 'primitive (cadr proc)))
       primitive-procedures))
(define (get-global-environment)
  the-global-environment)
(define (setup-environment)
  (let ((initial-env
          (extend-environment (primitive-procedure-names)
                              (primitive-procedure-objects)
                              the-empty-environment)))
    (define-variable! 'true true initial-env)
    (define-variable! 'false false initial-env)
    initial-env))
(define the-global-environment (setup-environment))

(define machine-operations
  (list (list 'self-evaluating? self-evaluating?)
        (list 'variable? variable?)
        (list 'quoted? quoted?)
        (list 'assignment? assignment?)
        (list 'definition? definition?)
        (list 'if? if?)
        (list 'lambda? lambda?)
        (list 'begin? begin?)
        (list 'application? application?)
        (list 'lookup-variable-value lookup-variable-value)
        (list 'text-of-quotation text-of-quotation)
        (list 'lambda-parameters lambda-parameters)
        (list 'lambda-body lambda-body)
        (list 'make-procedure make-procedure)
        (list 'operands operands)
        (list 'operator operator)
        (list 'empty-arglist empty-arglist)
        (list 'no-operands? no-operands?)
        (list 'first-operand first-operand)
        (list 'last-operand? last-operand?)
        (list 'rest-operands rest-operands)
        (list 'adjoin-arg adjoin-arg)
        (list 'primitive-procedure? primitive-procedure?)
        (list 'compound-procedure? compound-procedure?)
        (list 'apply-primitive-procedure apply-primitive-procedure)
        (list 'procedure-parameters procedure-parameters)
        (list 'procedure-environment procedure-environment)
        (list 'procedure-body procedure-body)
        (list 'extend-environment extend-environment)
        (list 'begin-actions begin-actions)
        (list 'first-exp first-exp)
        (list 'last-exp? last-exp?)
        (list 'rest-exps rest-exps)
        (list 'if-predicate if-predicate)
        (list 'true? true?)
        (list 'if-alternative if-alternative)
        (list 'if-consequent if-consequent)
        (list 'assignment-variable assignment-variable)
        (list 'assignment-value assignment-value)
        (list 'set-variable-value! set-variable-value!)
        (list 'definition-variable definition-variable)
        (list 'definition-value definition-value)
        (list 'define-variable! define-variable!)
        (list 'user-print user-print)
        (list 'prompt-for-input prompt-for-input)
        (list 'read read)
        (list 'get-global-environment get-global-environment)
        (list 'announce-output announce-output)
        (list 'primitive-procedures primitive-procedures)
        ; add everything missing...
        (list 'dump
              (lambda (x)
                (display x)
                (newline)))
        (list 'dump-environment
              (lambda (env)
                (display "Environment: ")
                (display (map frame-variables env)) 
                (newline)))))

(define eceval-registers '(exp env val proc argl continue unev))
(define eceval (make-machine eceval-registers
                             machine-operations
                             explicit-control-evaluator))

(define (apply-patch instructions after-label)
  (define (modify-original-evaluator! original-evaluator instructions after-label)
    (if (null? instructions)
        (error "Didn't find the label -- APPLY-PATCH" after-label)
        (if (eq? (car original-evaluator)
                 after-label)
            (set-cdr! original-evaluator
                      (append instructions
                              (cdr original-evaluator)))
            (modify-original-evaluator! (cdr original-evaluator)
                                        instructions
                                        after-label))))
  (modify-original-evaluator! explicit-control-evaluator instructions after-label)
  (set! eceval (make-machine eceval-registers
                             machine-operations
                             explicit-control-evaluator)))
(define (add-operation name proc)
  (set! machine-operations
        (cons (list name proc)
              machine-operations)))

(define (add-primitive-procedure name proc)
  (set! primitive-procedures
        (cons (list name proc)
              primitive-procedures))
  (set! the-global-environment (setup-environment)))

; total pushes are equal to 29+n*35
; maximum depth is equal to 10, constant
