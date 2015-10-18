; In mit-scheme, this gives an error:
; ;Premature reference to reserved name: a
;(let ((a 1))
;  (define (f x)
;    (define b (+ a x))
;    (define a 5)
;    (+ a b))
;  (f 10))
; To make this work we could try
(display (let ((a 1))
  (define (f x)
    (define b (lambda () (+ a x)))
    (define a 5)
    (+ a (b)))
  (f 10)))
; however, wrapping in lambda all the bodies of the defines would be inefficient
; and difficult as we would have to parse the trees at arbitrary depths
; plus, we would have to memoize the result to avoid side effects when one of the defined values is referred to multiple times
