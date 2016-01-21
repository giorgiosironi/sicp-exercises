(load "chapter5.4.scm")

; same as 5.26
; redefine the stack to measure statistics
(define (make-stack)
  (let ((s '())
        (number-pushes 0)
        (max-depth 0)
        (current-depth 0))
    (define (push x)
      (set! s (cons x s))
      (set! number-pushes (+ 1 number-pushes))
      (set! current-depth (+ 1 current-depth))
      (set! max-depth (max current-depth max-depth)))
    (define (pop)
      (if (null? s)
        (error "Empty stack -- POP")
        (let ((top (car s)))
          (set! s (cdr s))
          (set! current-depth (- current-depth 1))
          top)))
    (define (initialize)
      (set! s '())
      (set! number-pushes 0)
      (set! max-depth 0)
      (set! current-depth 0)
      'done)
    (define (print-statistics)
      (newline)(display (list 'total-pushes '= number-pushes
                              'maximum-depth '= max-depth)))
    (define (dispatch message)
      (cond ((eq? message 'push) push)
            ((eq? message 'pop) (pop))
            ((eq? message 'initialize) (initialize))
            ((eq? message 'print-statistics)
             (print-statistics))
            (else
              (error "Unknown request -- STACK" message))))
    dispatch))

; different primitive operations are needed
(add-primitive-procedure '= =)
(add-primitive-procedure '* *)
(add-primitive-procedure '- -)
(apply-patch
  '(stack-statistics-patch-start
    (perform (op print-stack-statistics))
    stack-statistics-patch-end)
  'print-result)

(start eceval)

; number of pushes = 32n - 16
; maximum depth = 3 + 5n
