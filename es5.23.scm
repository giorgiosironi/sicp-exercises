(load "chapter5.4.scm")
(load "es4.5.scm")

(apply-patch explicit-control-evaluator
             '(cond-if-patch-start
               (test (op cond?) (reg exp))
               ; for some reason we cannot get there
               ; because (cond ...) is interpreted as an application, I believe
               ; the problem is even if we patch this we have to create a new machine
               ; as the old one uses the original assembled evaluator
               ;(perform (op dump) (reg exp))
               )
             'extensions)
(add-operation 'cond?
               (lambda (exp) (display exp) (newline) (tagged-list? exp 'cond)))

(display explicit-control-evaluator)
(newline)

(start eceval)

