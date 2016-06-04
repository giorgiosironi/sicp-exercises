(load "chapter5.2.scm")
; b version
(define (make-save-b inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine
                             reg-name)))
      (lambda ()
        (push stack (list reg-name (get-contents reg)))
        (advance-pc pc)))))
(define (make-restore-b inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine
                             reg)))
      (lambda ()
        (let ((popped (pop stack)))
          (if (eq? reg-name (car popped))
              (set-contents! reg (cadr popped))
              (error "pushed one register but popped on another -- MAKE-RESTORE" (list reg-name popped))))
        (advance-pc pc)))))
; c version
; for each new register we add a stack to `stack` which is now an association list
(define (allocate-register-c name)
  (if (assoc name register-table)
    (error "Multiply defined register: " name)
    (begin 
      (set! register-table
        (cons (list name (make-register name))
              register-table))
      (set! stack
        (cons (list name (make-stack))
              stack))))
  'register-allocated)
; save and restore look up the stack using reg-name in the association list
(define (make-save-c inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine
                             reg-name)))
      (lambda ()
        (push (assoc reg-name stack)
              (list reg-name (get-contents reg)))
        (advance-pc pc)))))
(define (make-restore-c inst machine stack pc)
  (let ((reg-name (stack-inst-reg-name inst)))
    (let ((reg (get-register machine
                             reg)))
      (lambda ()
        (let ((popped (pop (assoc reg-name stack))))
          (if (eq? reg-name (car popped))
              (set-contents! reg
                             (cadr popped))
              (error "pushed one register but popped on another -- MAKE-RESTORE" (list reg-name popped))))
        (advance-pc pc)))))
