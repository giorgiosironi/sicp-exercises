(load "chapter5.5.scm")
(define (spread-arguments operands)
  (preserving '(env) ; not sure that to preserve,
                     ; arg1 and arg2 should work by themselves
                     ; as they are 'needs' from the two blocks
              (compile (car operands) 'arg1 'next)
              (compile (cadr operands) 'arg2 'next)))
(define (compile-= exp target linkage)
  (append-instruction-sequences
    (spread-arguments (operands exp))
    (let ((movement-from-val
           (if (eq? target 'val)
               '()
               ((assign target (reg val))))))
      (end-with-linkage linkage
                        (make-instruction-sequence '() (list 'val target)
                                                   (append `((perform (op =) (reg arg1) (reg arg2)))
                                                           movement-from-val))))))
; trying it out
(define expression '(= 1 2))
(dump (caddr (compile-= expression 'val 'next)))
