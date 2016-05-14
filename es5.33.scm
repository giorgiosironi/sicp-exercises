(load "chapter5.5.scm")
(define factorial-definition '(define (factorial-alt n)
                                (if (= n 1)
                                  1
                                  (* n (factorial-alt (- n 1))))))
(define (dump machine-instructions)
  (map (lambda (inst) 
         (display inst)
         (newline))
       machine-instructions))
(dump (caddr (compile factorial-definition 'val 'next)))


