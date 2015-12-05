; if we use set! rather than permanent-set! every increment to count
; will be reset upon searching a new value for the couple >x, y>
; therefore we will see count as 1 every time until the last failure,
; where we will see 0.
; The procedure is a simplified variation of analyze-assignment,
; as the failure continuation does not have to be decorated with rollback
; of the assignment
(define (analyze-permanent-assignment exp)
  ; assignment-variable and assignment-value do not change as only the 
  ; tag changes to 'permanent-assignment!
  (let ((var (assignment-variable exp))
        (vproc (analyze (assignment-value exp))))
    (lambda (env succeed fail)
      (vproc env
             (lambda (val fail2)
               (set-variable-value! var val env)
               (succeed 'ok fail2))
             fail))))
