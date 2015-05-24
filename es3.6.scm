; since once again the book is making us depend on code that 
; DOES NOT EXIST and we cannot test our program
(define (rand-update x)
  (+ x 1))
(define random-init 1000)
; beginning of the exercise
(define rand
  (let ((x random-init))
    (lambda (command)
      (cond ((eq? 'generate command)
             (begin (set! x (rand-update x))
                    x))
            ((eq? 'reset command)
             (lambda (new-value)
               (set! x new-value)))
            (else (error "Unknown command -- RAND"))))))
