; previously on SICP: redefine the stack to measure statistics
(load "chapter5.4.scm")
(load "chapter5.4.stack.scm")

; primitive procedures to deal with errors
(define (error? val)
  (tagged-list? val 'error))
(add-operation 'error? error?)

; point a: redefining lookup-variable-value to return an error
(define (env-loop env on-frame)
  (if (eq? env the-empty-environment)
    '(error lookup-variable)
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
; patching in error management
(apply-patch
    '((assign val (op lookup-variable-value) (reg exp) (reg env))
      (test (op error?) (reg val))
      (branch (label signal-error))
      (goto (reg continue)))
    'ev-variable)

; point b: errors in primitive procedures applications
(add-primitive-procedure '/ 
                         (lambda (a b)
                           (if (= b 0)
                               '(error division-by-zero)
                               (/ a b))))

(apply-patch
    '((assign val (op apply-primitive-procedure) (reg proc) (reg argl))
      (test (op error?) (reg val))
      (branch (label signal-error))
      (restore continue)
      (goto (reg continue)))
    'primitive-apply)

(start eceval)
