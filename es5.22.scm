; append! to be compiled
(define (append! x y)
  (set-cdr! (last-pair x) y)
  x)
(define (last-pair x)
  (if (null? (cdr x))
    x
    (last-pair (cdr x))))
; append to be compiled
(define (append x y)
  (if (null? x)
    y
    (cons (car x) (append (cdr x) y))))
(define append-machine-controller
  '(
    start-append
    (assign continue (label end-of-append))
    append
    (test (op null?) (reg x))
    (branch (label just-y))
    (assign temp (op car) (reg x))
    (save temp)
    (save continue)
    (assign x (op cdr) (reg x))
    (assign continue (label cons))
    (goto (label append))
    cons
    (restore continue)
    (restore temp)
    (assign val (op cons) (reg temp) (reg val))
    (goto (reg continue))
    just-y
    (assign val (reg y))
    (goto (reg continue))
    end-of-append))
(load "chapter5.2.scm")
(define append-machine (make-machine '(x y temp val continue)
                                     (list (list 'cons cons)
                                           (list 'car car)
                                           (list 'cdr cdr)
                                           (list 'null? null?)
                                           (list 'dump
                                                 (lambda (x)
                                                   (display x)
                                                   (newline))))
                                     append-machine-controller))
(set-register-contents! append-machine 'x '(1 2 3))
(set-register-contents! append-machine 'y '(4 5 6))
(start append-machine)
(display "Append result: ")
(display (get-register-contents append-machine 'val))
(newline)
