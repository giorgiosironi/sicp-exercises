(load "chapter5.5.scm")
(set! eceval-registers (append eceval-registers
                               '(compapp)))
(apply-patch '(start-of-5.47-patch-start
               (assign compapp (label compound-apply))
               (branch (label external-entry))
               end-of-5.47-patch-end)
             'start-of-machine)
(compile-and-go
  '(define (f n)
     (g n)))
