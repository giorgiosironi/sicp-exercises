(define (ripple-carry-adder a b s c)
  (if (not (null? a))
    (let ((c-in (generate-uninterned-symbol)))
      (full-adder (car a)
                  (car b)
                  c-in
                  (car s)
                  c)
      (ripple-carry-adder (cdr a)
                          (cdr b)
                          (cdr s)
                          c-in))))
; considering the carry as the bottleneck and n-bit numbers:
; half-adder-delay = (max (and-delay + not-delay) or-delay) + and-delay
; full-adder-delay = 2 * half-adder-delay + or-delay
; ripple-carry-delay = n * full-adder-delay
