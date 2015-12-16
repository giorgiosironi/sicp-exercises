; e.g. use 'jump instead of 'jump
(define (make-execution-procedure inst labels machine
                                  pc flag stack ops)
  (cond ((eq? (car inst) 'assign)
         (make-assign inst machine labels ops pc))
        ; ...
        ((eq? (car inst) 'jump)
         (make-jump inst machine labels pc))
        ; ...
        (else (error "Unknown instruction type -- ASSEMBLE"
                     inst))))
;;; jump
(define (make-jump inst machine labels pc)
  (let ((dest (jump-dest inst)))
    (cond ((label-exp? dest)
           (let ((insts
                   (lookup-label labels
                                 (label-exp-label dest))))
             (lambda () (set-contents! pc insts))))
          ((register-exp? dest)
           (let ((reg
                   (get-register machine
                                 (register-exp-reg dest))))
             (lambda ()
               (set-contents! pc (get-contents reg)))))
          (else (error "Bad jump instruction -- ASSEMBLE"
                       inst)))))
(define (jump-dest jump-instruction)
  (cadr jump-instruction))
; had to go up to make-execution-procedure to rename it, so it's a small change
; but at a distance
