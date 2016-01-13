(load "chapter5.4.scm")
(load "es4.5.scm")

(add-operation 'cond?
               (lambda (exp) (tagged-list? exp 'cond)))
(add-operation 'cond->if cond->if)
(apply-patch '(cond-if-patch-start
               (test (op cond?) (reg exp))
               (assign exp (op cond->if) (reg exp))
               (branch (label ev-if)))
             'extensions)

(start eceval)

