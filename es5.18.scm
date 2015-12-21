(load "chapter5.2.scm")
(define (make-register name)
  (let ((contents '*unassigned*)
        (trace #f))
    (define (dispatch message)
      (cond ((eq? message 'get) contents)
            ((eq? message 'set)
             (lambda (value)
               (if trace
                   (begin (display name)
                          (newline)
                          (display contents)
                          (display " => ")
                          (display value)
                          (newline))
                   'nothing)
               (set! contents value)
               ))
            ((eq? message 'trace-on)
             (set! trace #t))
            ((eq? message 'trace-off)
             (set! trace #f))
            (else
              (error "Unknown request -- REGISTER" message))))
    dispatch))
(define (register-trace-on machine register-name)
  ((get-register machine register-name) 'trace-on))
(define (register-trace-off machine register-name)
  ((get-register machine register-name) 'trace-off))
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
(register-trace-on factorial-machine 'n)
(start factorial-machine)
