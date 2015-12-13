(controller
  (assign continue (label fib-done))
  fib-loop
    (test (op <) (reg n) (const 2))
    (branch (label immediate-answer))
    (save continue)
    (assign continue (label afterfib-n-1))
    (save n)
    (assign n (op -) (reg n) (const 1))
    (goto (label fib-loop))
  afterfib-n-1
    (restore n)
    ; this one
    (restore continue)
    (assign n (op -) (reg n) (const 2))
    ; is offset by this one, I'm a compiler optimizer and I will delete them
    (save continue)
    (assign continue (label afterfib-n-2))
    (save val)
    (goto (label fib-loop))
  afterfib-n-2
    (assign n (reg val))
    (restore val)
    (restore continue)
    (assign val (op +) (reg val) (reg n)) ; Fib(n - 1) + Fib(n - 2)
    (goto (reg continue))
  immediate-answer
    (assign val (reg n))
    (goto (reg continue))
  fib-done)
