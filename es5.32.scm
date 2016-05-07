; previously on SICP: redefine the stack to measure statistics
(load "chapter5.4.scm")

; a. using an operation to understand whether to apply
;    the optimization of not saving the env register
(add-operation 'applying-symbol? (lambda (exp) (symbol? (car exp))))

; patching in optimization for applying when the operator is a symbol
(apply-patch
    '((test (op applying-symbol?) (reg exp))
      (branch (label optimized-application))
      ordinary-application
      (save continue)
      (save env)
      (assign unev (op operands) (reg exp))
      (save unev)
      (assign exp (op operator) (reg exp))
      (assign continue (label ev-appl-did-operator))
      (goto (label eval-dispatch))
      optimized-application
      (save continue)
      (assign unev (op operands) (reg exp))
      (save unev)
      (assign exp (op operator) (reg exp))
      (assign continue (label optimized-ev-appl-did-operator))
      (goto (label eval-dispatch))

      optimized-ev-appl-did-operator
      (restore unev) ; the operands
      (assign argl (op empty-arglist))
      (assign proc (reg val)) ; the operator
      (test (op no-operands?) (reg unev))
      (branch (label apply-dispatch))
      (save proc)
      (goto (label ev-appl-operand-loop))
      )
    'ev-application)

(start eceval)
; b. Alyssa would not eliminate the advantage of compilation, because the optimizations of the compiler are only performed at compile-time and not at each execution. The interpreter instead will perform them again each time the progran runs.
