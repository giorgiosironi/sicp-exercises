(define (unless->if exp)
  (let ((condition (cadr exp))
        (standard-value (caddr exp))
        (exceptional-value (cadddr exp)))
    (list 'if
          condition
          exceptional-value
          standard-value)))
(display (unless->if '(unless (= n 1)
                        (* n (factorial (- n 1)))
                        1)))
(newline)
; where unless can be useful as a procedure?
; Place zero instead of prime numbers...
; (map unless
;      (list #f #t #t #f #t)
;      (list 1 2 3 4 5)
;      (list 0 0 0 0 0))
