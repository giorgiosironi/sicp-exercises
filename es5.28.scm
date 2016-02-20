; previously on SICP: redefine the stack to measure statistics
(load "chapter5.4.scm")
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
(apply-patch
  '(stack-statistics-patch-start
    (perform (op print-stack-statistics))
    stack-statistics-patch-end)
  'print-result)

; procedures to run factorials
(add-primitive-procedure '> >)
(add-primitive-procedure '* *)
(add-primitive-procedure '= =)
(add-primitive-procedure '- -)

; we need to substitute ev-sequence-last-exp
(define non-tail-recursive-patch 
    '(ev-sequence-last-exp
      (save unev)
      (save env)
      (assign continue (label ev-sequence-last-exp-continue))
      (goto (label eval-dispatch))
      ev-sequence-last-exp-continue
      (restore env)
      (restore unev)
      (restore continue)
      (goto (reg continue))))

(define non-tail-recursive-patch 
    '(non-tail-recursive-patch-start
      (save unev)
      (save env)
      (assign continue (label ev-sequence-last-exp-continue))
      (goto (label eval-dispatch))
      ev-sequence-last-exp-continue
      (restore env)
      (restore unev)
      (restore continue)
      (goto (reg continue))
      non-tail-recursive-patch-end))

(apply-patch non-tail-recursive-patch
             'ev-sequence-last-exp)

(start eceval)
