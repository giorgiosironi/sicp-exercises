; previously on SICP
(load "chapter5.2.scm")
; from es5.6
(define fibonacci-controller
  '((assign continue (label fib-done))
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
    fib-done))
; make-machine facade
(define (instruction-text inst)
  (car inst))
(define (make-new-machine)
  (let ((pc (make-register 'pc))
        (flag (make-register 'flag))
        (stack (make-stack))
        (the-instruction-sequence '())
        (instructions-types '())
        (registers-for-entry-points '())
        (registers-for-stack '()))
    (let ((the-ops
            (list (list 'initialize-stack
                        (lambda () (stack 'initialize)))))
          (register-table
            (list (list 'pc pc) (list 'flag flag))))
      ; ...start not changed
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
              ((instruction-execution-proc (car insts)))
              (execute)))))
      ; ...end not changed
      (define (extract-instruction-types seq)
       (merge-sort (delete-duplicates (map car (map instruction-text seq)))
                   (lambda (x y)
                     (string<? (symbol->string x)
                               (symbol->string y)))))
      (define (extract-registers-for-entry-points insts)
        (define (operation-exp-name inst)
          (car (car inst)))
        (define (operation-exp-first-operand inst)
          (car (operation-exp-operands (car inst))))
        (define (inst-goto? inst)
          (eq? 'goto (operation-exp-name inst)))
        (define (operand-register? inst)
          (eq? 'reg
               (car (operation-exp-first-operand inst))))
        (delete-duplicates (map (lambda (op)
                                  (register-exp-reg (operation-exp-first-operand op)))
                                (filter operand-register?
                                        (filter inst-goto?
                                                insts)))))
      ;define (extract-registers-for-stack ops)
      ; (delete-duplicates (map (lambda (op)
      ;                           (register-exp-reg (car (operation-exp-operands op))))
      ;                         (filter (lambda (op) 
      ;                                   (or (eq? 'save (operation-exp-op op))
      ;                                       (eq? 'restore (operation-exp-op op))))
      ;                                 ops))))
      (define (dispatch message)
        (cond ((eq? message 'start)
               (set-contents! pc the-instruction-sequence)
               (execute))
              ((eq? message 'install-instruction-sequence)
               (lambda (seq)
                 (set! the-instruction-sequence seq)
                 (set! instructions-types (extract-instruction-types seq))
                 (set! registers-for-entry-points (extract-registers-for-entry-points seq))))
              ((eq? message 'allocate-register) allocate-register)
              ((eq? message 'get-register) lookup-register)
              ((eq? message 'install-operations)
               (lambda (ops)
                 (set! the-ops (append the-ops ops))
                 ;(set! registers-for-stack (extract-registers-for-stack ops))
                 ; TODO parse assignments here to get the map of sources for assignment from each register
                 ))
              ((eq? message 'stack) stack)
              ((eq? message 'operations) the-ops)
              ((eq? message 'instruction-types) instructions-types)
              ((eq? message 'registers-for-entry-points) registers-for-entry-points)
              ; TODO: add accessors for new data path information
              (else (error "Unknown request -- MACHINE" message))))
      dispatch)))
; have to redefine this to bind in the new make-new-machine
(define (make-machine register-names ops controller-text)
  (let ((machine (make-new-machine)))
    (for-each (lambda (register-name)
                ((machine 'allocate-register) register-name))
              register-names)
    ((machine 'install-operations) ops)
    ((machine 'install-instruction-sequence)
     (assemble controller-text machine))
    machine))
(define fibonacci-machine
  (make-machine '(n val continue)
                (list (list '+ +)
                      (list '- -)
                      (list '< <))
                fibonacci-controller))

(display (fibonacci-machine 'instruction-types))
(newline)
(display (fibonacci-machine 'registers-for-entry-points))
(newline)
