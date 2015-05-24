(define f 
  (let ((current-value -1))
    (lambda (new-value)
      (let ((old-value current-value))
        (begin (set! current-value new-value)
               old-value)))))
(define (evaluate-f-direction-one) (+ (f 0) (f 1)))
; notice you have to restart the program before calling the second
; of these functions, since they share state
(define (evaluate-f-direction-two) (+ (f 1) (f 0)))
