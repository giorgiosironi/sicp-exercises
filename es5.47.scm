(load "chapter5.5.scm")
(set! eceval-registers (append eceval-registers
                               '(compapp)))
(apply-patch '(start-of-5.47-patch-start
               (assign compapp (label compound-apply))
               (branch (label external-entry))
               end-of-5.47-patch-end)
             'start-of-machine)
; redefining the compiling of procedure call, 
; to:
; - a primitive procedure (+)
; - a compiled procedure (defined at the startup of the interpreter)
; - an interpreted aka compound procedure (defined using the interpreter)
; the primitive branch is directly specified here
(define (compile-procedure-call target linkage)
  (let ((primitive-branch (make-label 'primitive-branch))
        (compiled-branch (make-label 'compiled-branch))
        (interpreted-branch (make-label 'interpreted-branch))
        (after-interpreted-call (make-label 'after-interpreted-call))
        (after-call (make-label 'after-call)))
    (let ((compiled-linkage
            (if (eq? linkage 'next) after-call linkage)))
      (append-instruction-sequences
        (make-instruction-sequence '(proc) '()`((test (op primitive-procedure?) (reg proc))
                                                (branch (label ,primitive-branch))
                                                (test (op compound-procedure?) (reg proc))
                                                (branch (label ,interpreted-branch))))
        ; parallel because they won't be executed sequentially
        (parallel-instruction-sequences
          (parallel-instruction-sequences
            (append-instruction-sequences
              compiled-branch
              (compile-proc-appl target compiled-linkage))
            (append-instruction-sequences
              primitive-branch
              (end-with-linkage linkage
                                (make-instruction-sequence '(proc argl)
                                                           (list target)
                                                           `((assign ,target
                                                                     (op apply-primitive-procedure)
                                                                     (reg proc)
                                                                     (reg argl)))))))
          (append-instruction-sequences 
            interpreted-branch
            (end-with-linkage linkage
                              (make-instruction-sequence '(proc argl)
                                                         '(continue)
                                                         `((perform (op dump) (const "INTERPRETED-BRANCH"))
                                                           (assign continue (label ,after-interpreted-call))
                                                           (goto (reg compapp))
                                                           ,after-interpreted-call)))))
          after-call))))
(compile-and-go
  '(define (f n)
     (g n)))
