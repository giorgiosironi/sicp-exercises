(controller
  (assign counter (const 1))
  (assign product (const 1))
  test-counter
      (test (op >) (reg counter) (reg n))
      (branch (label factorial-done))
      (assign t (op *) (reg counter) (reg product))
      (assign product (reg t))
      (assign t (op +) (const 1) (reg counter))
      (goto (label test-counter))
  factorial-done)

