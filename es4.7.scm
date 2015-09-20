; from 4.6, but refactored with let-bindings
(define (let-bindings exp)
  (cadr exp))
(define (let-vars exp)
  (map (lambda (binding) (car binding))
       (let-bindings exp)))
(define (let-exps exp)
  (map (lambda (binding) (cadr binding))
       (let-bindings exp)))
(define (let-body exp)
  (caddr exp))
; exercise
(define (make-let bindings body)
  (list 'let bindings body))
(define (let*->nested-lets exp)
  (make-let
    (list (car (let-bindings exp)))
    (let ((rest-bindings (cdr (let-bindings exp)))
          (body (let-body exp)))
      (if (null? rest-bindings)
          body
          (let*->nested-lets (make-let rest-bindings body))))))
(display (let*->nested-lets '(let* ((x 3) (y (+ x 2)) (z (+ x y 5))) (* x z))))
(newline)
