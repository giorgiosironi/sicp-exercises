(define (append! x y)
  (set-cdr! (last-pair x) y)
  x)
(define (last-pair x)
  (if (null? (cdr x))
    x
    (last-pair (cdr x))))

(define x (list 'a 'b))
(define y (list 'c 'd))
(define z (append x y))

; first response is '(b)
; since x is kept immutable
; x => [a|b|nil]
; y => [c|d|nil]
; z = [a|b|y]

; second response is '(b c d)
; since x is modified in its last-pair
; x => [a|b|y]
; y => [c|d|nil]
; z = x
