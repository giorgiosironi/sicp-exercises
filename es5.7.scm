; as it often happens with SICP
; no way of running this code since there is no code for the simulator up to this point of the book
; here is I would I test expt
(define expt-machine
  (make-machine
    '(n counter product b)
    (list (list '= =)
          (list '- -)
          (list '* *))
    '(controller 
       (assign counter (reg n))
       (assign product (const 1))
       expt-loop
       (test (op =) (reg counter) (const 0))
       (branch (label expt-done))
       (assign counter (op -) (reg counter) (const 1))
       (assign product (op *) (reg b) (reg product))
       (goto (label expt-loop))
       expt-done)))
(set-register-contents! expt-machine 'n 10)
(set-register-contents! expt-machine 'b 5)
(start expt-machine)
(display (get-register-contents expt-machine 'product))
