(load "chapter5.2.scm")
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
        (the-instruction-sequence '())
        (instruction-tracing #f))
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
              (if instruction-tracing
                  (begin (display (car (car insts)))
                         (newline))
                  'nothing)
              ; if there is execution counting here we should not increment the counter if (car (car insts)) is a (label ...)
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
              ((eq? message 'instruction-tracing-on) (set! instruction-tracing #t))
              ((eq? message 'instruction-tracing-off) (set! instruction-tracing #f))
              (else (error "Unknown request -- MACHINE" message))))
      dispatch)))
(define (extract-labels text receive)
  (if (null? text)
    (receive '() '())
    (extract-labels (cdr text)
                    (lambda (insts labels)
                      (let ((next-inst (car text)))
                        (if (symbol? next-inst)
                          ; case of a label
                          ; we add an additional fake instruction
                          ; so that insts become new-insts
                          (let ((fake-label-instruction (list (list 'label
                                                                    next-inst)
                                                              next-inst)))
                            (let ((new-insts (cons fake-label-instruction
                                                   insts)))
                                ; insts are now one more for each label encountered
                                (receive new-insts
                                         ; label entry points to new-insts
                                         ; the simulator will have to somewhat execute the label
                                         (cons (make-label-entry next-inst
                                                                 new-insts)
                                               labels))))
                          ; case of an instruction
                          (receive (cons (make-instruction next-inst)
                                         insts)
                                   labels)))))))
(define (make-execution-procedure inst labels machine
                                  pc flag stack ops)
  (cond ((eq? (car inst) 'label)
         (make-label pc))
        ((eq? (car inst) 'assign)
         (make-assign inst machine labels ops pc))
        ((eq? (car inst) 'test)
         (make-test inst machine labels ops flag pc))
        ((eq? (car inst) 'branch)
         (make-branch inst machine labels flag pc))
        ((eq? (car inst) 'goto)
         (make-goto inst machine labels pc))
        ((eq? (car inst) 'save)
         (make-save inst machine stack pc))
        ((eq? (car inst) 'restore)
         (make-restore inst machine stack pc))
        ((eq? (car inst) 'perform)
         (make-perform inst machine labels ops pc))
        (else (error "Unknown instruction type -- ASSEMBLE"
                     inst))))
(define (make-label pc)
  (lambda ()
    (advance-pc pc)))
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

(factorial-machine 'instruction-tracing-on)
(set-register-contents! factorial-machine 'n 6)
(start factorial-machine)
