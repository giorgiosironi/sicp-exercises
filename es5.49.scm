(load "chapter5.5.scm")
(define explicit-control-evaluator-that-compiles '(
    start-of-machine
    read-eval-print-loop
    (perform (op initialize-stack))
    (perform (op prompt-for-input) (const ";;; EC-Eval input:"))
    (assign exp (op read))
    (assign env (op get-global-environment))
    (assign continue (label print-result))
    (goto (label compile-and-execute-dispatch))
    compile-and-execute-dispatch
    (assign val (op compile) (reg exp) (const val) (const return))
    (assign val (op statements) (reg val))
    (assign val (op assemble-on-global-machine) (reg val))
    (goto (label external-entry))
    ; label to target for patching in derived expressions
    extensions
    print-result
    (perform (op announce-output) (const ";;; EC-Eval value:"))
    (perform (op user-print) (reg val))
    (goto (label read-eval-print-loop))
    end-of-machine
    external-entry
    (perform (op initialize-stack))
    (assign env (op get-global-environment))
    ; uncomment to see what gets executed during initial compilation
    ; basically code constructing the compiled procedure
    ; and modifying the global environment to expose it
    ; (perform (op dump) (reg val))
    (assign continue (label print-result))
    (goto (reg val))
    external-entry-patch-end)
    )

(add-operation 'compile compile)
(add-operation 'statements statements)
(add-operation 'assemble-on-global-machine
               (lambda (statements)
                 (assemble statements eceval)))
(set! eceval (make-machine eceval-registers
                           machine-operations
                           explicit-control-evaluator-that-compiles))
(start-machine)
