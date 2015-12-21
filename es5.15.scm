(load "chapter5.2.scm")
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
        (the-instruction-sequence '())
        (instruction-count 0))
    (let ((the-ops
            (list (list 'initialize-stack
                        (lambda () (stack 'initialize)))
                  (list 'print-stack-statistics
                        (lambda () (stack 'print-statistics)))))
          (register-table
            (list (list 'pc pc) (list 'flag flag))))
      (define (allocate-register name)
        (if (assoc name register-table)
          (error "Multiply defined register: " name)
          (set! register-table
            (cons (list name (make-register name))
                  register-table)))
        'register-allocated)
      (define (lookup-register name)
        (let ((val (assoc name register-table)))
          (if val
            (cadr val)
            (error "Unknown register:" name))))
      (define (execute)
        (let ((insts (get-contents pc)))
          (if (null? insts)
            'done
            (begin
              (set! instruction-count (+ instruction-count 1))
              ((instruction-execution-proc (car insts)))
              (execute)))))
      (define (dispatch message)
        (cond ((eq? message 'start)
               (set-contents! pc the-instruction-sequence)
               (execute))
              ((eq? message 'install-instruction-sequence)
               (lambda (seq) (set! the-instruction-sequence seq)))
              ((eq? message 'allocate-register) allocate-register)
              ((eq? message 'get-register) lookup-register)
              ((eq? message 'install-operations)
               (lambda (ops) (set! the-ops (append the-ops ops))))
              ((eq? message 'stack) stack)
              ((eq? message 'operations) the-ops)
              ((eq? message 'instruction-count-get) instruction-count)
              ((eq? message 'instruction-count-reset) (set! instruction-count 0))
              (else (error "Unknown request -- MACHINE" message))))
      dispatch)))
; inputs
(define factorial-controller
  '((assign continue (label fact-done))
    fact-loop
      (test (op =) (reg n) (const 1))
      (branch (label base-case))
      (save continue)
      (save n)
      (assign n (op -) (reg n) (const 1))
      (assign continue (label after-fact))
      (goto (label fact-loop))
    after-fact
      (restore n)
      (restore continue)
      (assign val (op *) (reg n) (reg val))
      ; val now contains n(n - 1)!
      (goto (reg continue))
    ; return to caller
    base-case
    (assign val (const 1))
    ; base case: 1! = 1
    (goto (reg continue))
    ; return to caller
    fact-done))
(define factorial-machine (make-machine '(n val continue)
                                        (list (list '= =)
                                              (list '- -)
                                              (list '* *))
                                        factorial-controller))
(set-register-contents! factorial-machine 'n 6)
(start factorial-machine)
(display (factorial-machine 'instruction-count-get))
(newline)
(factorial-machine 'instruction-count-reset)
(display (factorial-machine 'instruction-count-get))
(newline)
(start factorial-machine)
(display (factorial-machine 'instruction-count-get))
(newline)
