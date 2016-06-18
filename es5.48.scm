(load "chapter5.5.scm")
; define here compile-and-run, it should
; + 1. compile the code
; + 2. add a register to hold the external-entry entry point,
;    because we will need to jump there
; 4. put the compiled code into 'val
; 5. modify 'continue to go to the 'external-entry label, which will 
;   take 'val and execute it, and then go to 'print-result
(set! eceval-registers (append eceval-registers
                               '(compiling-entry-point)))
(apply-patch '(start-of-5.48-patch-start
               (assign compiling-entry-point (label external-entry))
               end-of-5.48-patch-end)
             'start-of-machine)
(define (compile-and-run expression)
  (let* ((compiled-statements
          (statements (compile expression 'val 'return)))
         (instructions
          (assemble compiled-statements
                    eceval)))
    ;(display "COMPILING NEW INSTRUCTIONS...")
    ;(display compiled-statements)
    ;(newline)
    (set-register-contents! eceval
                            'val
                            instructions)
    ; this will be restored in 'continue
    ; and we are now able to derail execution to the compiling-entry-point
    ; but, then there is an error on the goto to val,
    ; maybe we did not set the 'val register correctly
    (push (eceval 'stack) (get-register-contents eceval 'compiling-entry-point))
    ; the returned value overwrites 'val
    instructions))
(add-primitive-procedure 'compile-and-run compile-and-run)

(start-machine)
