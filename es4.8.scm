; library
(define (make-lambda parameters body)
  (cons 'lambda (cons parameters body)))
(define (make-application proc parameters)
  (cons proc parameters))
(define (make-let vars exps body)
  (list 'let
        (make-let-bindings vars exps)
        body))
(define (make-let-bindings vars exps)
  (map (lambda (var exp)
         (list var exp))
       vars
       exps))
(define (let-vars exp)
  (map (lambda (binding) (car binding))
       (cadr exp)))
(define (let-exps exp)
  (map (lambda (binding) (cadr binding))
       (cadr exp)))
(define (let-body exp)
  (caddr exp))
; exercise
(define (named-let-name exp)
  (cadr exp))
(define (named-let-vars exp)
  (map (lambda (binding) (car binding))
       (caddr exp)))
(define (named-let-exps exp)
  (map (lambda (binding) (cadr binding))
       (caddr exp)))
(define (named-let-body exp)
  (cadddr exp))
(define (make-define variable value)
  (list 'define variable value))
(define (let->combination exp)
  (if (= (length exp) 4)
      (named-let->combination exp)
      (make-application (make-lambda (let-vars exp)
                                     (list (let-body exp)))
                        (let-exps exp))))
(define (named-let->combination exp)
  (make-application
    (make-lambda '()
                 (list (list 'begin
                             (make-define 
                               (named-let-name exp)
                               (make-lambda (named-let-vars exp)
                                            (list (named-let-body exp))))
                             (make-application (named-let-name exp)
                                               (named-let-exps exp)))))
    '()))
(display (let->combination '(let ((x 3) (y 2)) (+ x y))))
(newline)
(display (let-body '(let ((x 3) (y 2)) (+ x y))))
(newline)
(display (let->combination '(let factorial-iter ((input 6) (i 1) (result 1)) (if (> i input) result (factorial-iter input (+ i 1) (* i result))))))
(newline)