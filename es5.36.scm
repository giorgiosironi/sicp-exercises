(load "chapter5.5.scm")
(define expression '(begin
                      (define (id x)
                        (debug x)
                        x)
                      (define (devnull arg1 arg2) 'nothing)
                      (devnull (id "A") (id "B"))))
; this evaluates operands right to left
(compile-and-execute expression)
; redefining argument list construction without reversing the
; operand-codes. The base case of the recursion is
; code-to-get-first-arg, not code-to-get-last-arg
; we have to introduce reverse as an operation like cons,
; because the list constructed at runtime is in opposite
; order, and at runtime we have to reverse it
(define (construct-arglist operand-codes)
  (if (null? operand-codes)
    ; 0-argument case
    (make-instruction-sequence '() '(argl)
                               '((assign argl (const ()))))
    (let ((code-to-get-first-arg
            (append-instruction-sequences
              (car operand-codes)
              (make-instruction-sequence '(val) '(argl)
                                         '((assign argl (op list) (reg val)))))))
      (if (null? (cdr operand-codes))
        ; 1-argument case
        code-to-get-first-arg
        (append-instruction-sequences
          (preserving '(env)
                      code-to-get-first-arg
                      (code-to-get-rest-args
                        (cdr operand-codes)))
          (make-instruction-sequence 
            '(argl)
            '(argl)
            '((assign argl (op reverse) (reg argl)))))))))

(add-operation 'reverse reverse)
; this now evaluates left to right
(compile-and-execute expression)
; efficiency is that we introduce a reverse call at runtime
; rather than a reverse call at compile time
; This is for sure less efficient as it is work that didn't 
; have to be done in the previous version; this is true
; especially if reverse is implemented in terms of cons, car
; and cdr rather than as a machine operation. It cannot 
; be implemented as a procedure (either primitive or compiled)
; because we are using it in procedure application...
