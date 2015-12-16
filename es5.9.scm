; modify make-primitive-exp to not allow labels
(define (make-primitive-exp-for-operations exp machine labels)
  (cond ((constant-exp? exp)
         (let ((c (constant-exp-value exp)))
           (lambda () c)))
        ((register-exp? exp)
         (let ((r (get-register machine
                                (register-exp-reg exp))))
           (lambda () (get-contents r))))
        (else
          (error "Unknown expression type -- ASSEMBLE" exp))))
; call the new version from make-operation-exp,
; without modifying the original make-primitive-exp which is used 
; in make-assign and should allow labels
(define (make-operation-exp exp machine labels operations)
  (let ((op (lookup-prim (operation-exp-op exp) operations))
        (aprocs
          (map (lambda (e)
                 (make-primitive-exp-for-operations e machine labels))
               (operation-exp-operands exp))))
    (lambda ()
      (apply op (map (lambda (p) (p)) aprocs)))))
