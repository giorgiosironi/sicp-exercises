(define count-leaves-controller
  '(count-leaves-start
    (assign continue (label end-of-machine))
    count-leaves-proc
    (test (op null?) (reg tree))
    (branch (label zero))
    (assign test (op pair?) (reg tree))
    (assign test (op not) (reg test))
    ; check test available syntax
    (test (op true?) (reg test))
    (branch (label one))
    (save tree)
    (assign tree (op car) (reg tree))
    (save continue)
    (assign continue (label continue-count-leaves-1))
    (goto (label count-leaves-proc))
    continue-count-leaves-1
    (restore continue)
    (restore tree)
    (assign a (reg val))
    (save a)
    (save tree)
    (assign tree (op cdr) (reg tree))
    (save continue)
    (assign continue (label continue-count-leaves-2))
    (goto (label count-leaves-proc))
    continue-count-leaves-2
    (restore continue)
    (restore tree)
    (restore a)
    (assign b (reg val))
    (assign val (op +) (reg a) (reg b))
    (goto (label end-count-leaves))
    zero
    (assign val (const 0))
    (goto (label end-count-leaves))
    one
    (assign val (const 1))
    (goto (label end-count-leaves))
    end-count-leaves
    (goto (reg continue))
    end-of-machine))
(load "chapter5.2.scm")
(define count-leaves-machine (make-machine '(test tree a b val continue)
                                           (list (list '+ +)
                                                 (list 'car car)
                                                 (list 'cdr cdr)
                                                 (list 'pair? pair?)
                                                 (list 'null? null?)
                                                 (list 'true? (lambda (x) x))
                                                 (list 'not not)
                                                 (list 'dump
                                                       (lambda (x)
                                                         (display x)
                                                         (newline))))
                                           count-leaves-controller))
(define tree (cons (cons 1 2) (cons 3 (cons 4 5))))
(set-register-contents! count-leaves-machine 'tree tree)
(start count-leaves-machine)
(display "Counted leaves: ")
(display (get-register-contents count-leaves-machine 'val))
(newline)
