; previously on SICP: redefine the stack to measure statistics
(load "chapter5.4.scm")
(load "chapter5.4.stack.scm")

; redefining lookup-variable-value to return an error
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
; primitive procedures to deal with errors
(define (error? val)
  (tagged-list? val 'error))
(add-primitive-procedure 'error? error?)

; patching in error management
(apply-patch
    '((assign val (op lookup-variable-value) (reg exp) (reg env))
      (goto (reg continue)))
    'ev-variable)

(start eceval)
