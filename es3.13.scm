(define (make-cycle x)
  (set-cdr! (last-pair x) x)
  x)
(define z (make-cycle (list 'a 'b 'c)))

; z = [a|b|c|z]
; of course last-pair is an infinite recursion
