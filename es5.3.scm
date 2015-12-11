; first iteration: good-enough? and improve? are available as primitives
(controller
  (assign guess (const 1.0))
  test-good-enough
    (test (op good-enough?) (reg guess))
    (branch (label sqrt-done))
    (assign t (op improve) (reg guess))
    (assign guess (reg t))
  sqrt-done)
; second iteration: guess and good enough are implemented in terms of arithmetic operations
(controller
  (assign guess (const 1.0))
  test-good-enough
    (assign t1 (op *) (reg guess) (reg guess))
    (assign t2 (op -) (reg t1) (reg x))
    (assign t1 (op abs) (reg t2))
    (test (op <) (reg t1) (const 0.001))
    (branch (label sqrt-done))
    (assign t1 (op /) (reg x) (reg guess))
    (assign t2 (op +) (reg guess) t1)
    (assign guess (op /) (reg t2) (const 2))
  sqrt-done)
