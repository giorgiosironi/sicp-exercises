(load "chapter5.5.scm")
(define expression '(define (f x)
                      (+ x (g (+ x 2)))))
(define (dump machine-instructions)
  (map (lambda (inst) 
         (display inst)
         (newline))
       machine-instructions))
(dump (caddr (compile expression 'val 'next)))


