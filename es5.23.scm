(load "chapter5.4.scm")
(load "es4.5.scm")

(add-operation 'cond?
               (lambda (exp) (tagged-list? exp 'cond)))
(add-operation 'cond->if cond->if)
(apply-patch '(cond-if-patch-start
               (test (op cond?) (reg exp))
               (branch (label ev-cond-if))
               (goto (label cond-if-patch-end))
               ev-cond-if
               (assign exp (op cond->if) (reg exp))
               (branch (label ev-if))
               cond-if-patch-end)
             'extensions)

(start eceval)

