; previously on SICP: redefine the stack to measure statistics
(load "chapter5.4.scm")
(load "chapter5.4.stack.scm")

; procedures to run factorials
(add-primitive-procedure '> >)
(add-primitive-procedure '* *)
(add-primitive-procedure '= =)
(add-primitive-procedure '- -)

; we need to substitute ev-sequence-last-exp
(define non-tail-recursive-patch 
    '(ev-sequence-last-exp
      (save unev)
      (save env)
      (assign continue (label ev-sequence-last-exp-continue))
      (goto (label eval-dispatch))
      ev-sequence-last-exp-continue
      (restore env)
      (restore unev)
      (restore continue)
      (goto (reg continue))))

(define non-tail-recursive-patch 
    '(non-tail-recursive-patch-start
      (save unev)
      (save env)
      (assign continue (label ev-sequence-last-exp-continue))
      (goto (label eval-dispatch))
      ev-sequence-last-exp-continue
      (restore env)
      (restore unev)
      (restore continue)
      (goto (reg continue))
      non-tail-recursive-patch-end))

(apply-patch non-tail-recursive-patch
             'ev-sequence-last-exp)

(start eceval)
