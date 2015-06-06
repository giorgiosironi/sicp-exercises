; seems to be a reverse function
(define (mystery x)
  (define (loop x y)
    (if (null? x)
        y
        (let ((temp (cdr x)))
          (set-cdr! x y)
          (loop temp x))))
  (loop x '()))
(define v '(a b c d))
(define w (mystery v))

; v was a list starting with 'a but, to reverse it,
; (set-cdr! v '())
; was called. So it became '(a)
;
; w is the result of the reverse:
; '(d c b a)
