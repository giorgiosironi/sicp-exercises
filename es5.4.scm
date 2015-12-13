; recursive
(controller
  (assign continue (label expt-done))
  expt-loop
    (test (op =) (reg n) (const 0))
    (branch (label immediate-answer))
    (save continue)
    (save n)
    (assign n (op -) (reg n) (const 1))
    (assign continue (label after-expt-n-1))
    (goto (label expt-loop))
  after-expt-n-1
    (restore n)
    (assign val (op *) (reg n) (reg val))
    (restore continue)
    (goto (reg continue))
  immediate-answer
    (assign val (const 1))
    (goto (reg continue))
  expt-done)
; iterative
(controller 
  (assign counter (reg n))
  (assign product (const 1))
  expt-loop
    (test (op =) (reg counter) (const 0))
    (branch (label expt-done))
    (assign counter (op -) (reg counter) (const 1))
    (assign product (op *) (reg b) (reg product))
    (goto (label expt-loop))
  expt-done)
