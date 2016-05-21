(load "chapter5.5.scm")
; trying some sums
(define expression '(+ (+ 1 2) 3))
; original optimized compilation
(dump (caddr (compile expression 'val 'next)))
; modifying preserving to reintroduce wasteful saves
(define (preserving regs seq1 seq2)
  (if (null? regs)
    (append-instruction-sequences seq1 seq2)
    (let ((first-reg (car regs)))
      (if ;(and 
            (needs-register? seq2 first-reg)
            ; we don't want to save everything
            ; but we can remove the condition
            ; that the first blocks modifies
            ; the register that we need later
            ;(modifies-register? seq1 first-reg))
        (preserving (cdr regs)
                    (make-instruction-sequence
                      (list-union (list first-reg)
                                  (registers-needed seq1))
                      (list-difference (registers-modified seq1)
                                       (list first-reg))
                      (append `((save ,first-reg))
                              (statements seq1)
                              `((restore ,first-reg))))
                    seq2)
        (preserving (cdr regs) seq1 seq2)))))
(dump (caddr (compile expression 'val 'next)))
