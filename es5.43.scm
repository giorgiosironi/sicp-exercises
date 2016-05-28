(load"es5.42.scm")
; taken from es4.16.scm
(define (scan-out-defines procedure-body)
  (define (make-let vars exps body)
    (cons 'let
          (cons (make-let-bindings vars exps)
                body)))
  (define (make-let-bindings vars exps)
    (map (lambda (var exp)
           (list var exp))
         vars
         exps))
  (define (new-body names values remaining-body)
    (if (null? names)
      (cons 'begin remaining-body)
      (make-let names 
                ; YOU are a problem 
                (map (lambda (names) ''*unassigned)
                     names)
                (append
                  (map (lambda (name value)
                         (list 'set! name value))
                       names
                       values)
                  remaining-body))))
  (define (iter-scan-out procedure-body names values executable-body)
    (if (null? procedure-body)
        (new-body names values executable-body)
        (let ((expression (car procedure-body)))
          (if (define? expression)
              (iter-scan-out (cdr procedure-body)
                             (cons (define-name expression)
                                   names)
                             (cons (define-value expression)
                                   values)
                             executable-body)
              (iter-scan-out (cdr procedure-body)
                             names
                             values
                             (append executable-body
                                     (list expression)))))))
  (iter-scan-out procedure-body '() '() '()))
(define (define? expression)
  (and (pair? expression)
       (eq? 'define (car expression))))
(define (define-name expression)
  (cadr expression))
(define (define-value expression)
  (caddr expression))
; we have to modify the compilation of lambdas, which also 
; is used in compiling procedure definition
(define (compile-lambda-body exp proc-entry compile-environment)
  (define (many-unassigned another-list)
    (if (null? another-list)
      '()
      (cons '*unassigned (many-unassigned (cdr another-list)))))
  (let* ((formals (lambda-parameters exp))
         (extended-environment (extend-environment 
                                  formals
                                  (many-unassigned formals)
                                  compile-environment)))

    (append-instruction-sequences
      (make-instruction-sequence '(env proc argl) '(env)
                                 `(,proc-entry
                                    (assign env (op compiled-procedure-env) (reg proc))
                                    (assign env
                                            (op extend-environment)
                                            (const ,formals)
                                            (reg argl)
                                            (reg env))))
      (compile (scan-out-defines (lambda-body exp))
               'val
               'return 
               extended-environment))))
; the compiler in the book didn't fucking implement let expressions
; so we have to do that first
(define (let->combination exp)
  (define (make-lambda parameters body)
    (cons 'lambda (cons parameters body)))
  ; exercise
  (define (make-application proc parameters)
    (cons proc parameters))
  (define (let-vars exp)
    (map (lambda (binding) (car binding))
         (cadr exp)))
  (define (let-exps exp)
    (map (lambda (binding) (cadr binding))
         (cadr exp)))
  (define (let-body exp)
    (cddr exp))
  (make-application (make-lambda (let-vars exp)
                                 (let-body exp))
                    (let-exps exp)))
(define (let? exp) (tagged-list? exp 'let))
; adding let-case into compile...
(define (compile exp target linkage compile-environment)
  (cond ((self-evaluating? exp)
		 (compile-self-evaluating exp target linkage compile-environment))
		((quoted? exp) (compile-quoted exp target linkage compile-environment))
		((variable? exp)
		 (compile-variable exp target linkage compile-environment))
		((assignment? exp)
		 (compile-assignment exp target linkage compile-environment))
		((definition? exp)
		 (compile-definition exp target linkage compile-environment))
		((if? exp) (compile-if exp target linkage compile-environment))
		((lambda? exp) (compile-lambda exp target linkage compile-environment))
		((begin? exp)
		 (compile-sequence (begin-actions exp)
						   target
						   linkage
                           compile-environment))
		((cond? exp) (compile (cond->if exp) target linkage compile-environment))
        ((let? exp) (compile (let->combination exp) target linkage compile-environment))
		((application? exp)
		 (compile-application exp target linkage compile-environment))
		(else
		  (error "Unknown expression type -- COMPILE" exp))))
(define (compile-self-evaluating exp target linkage compile-environment)
  (end-with-linkage linkage
                    (make-instruction-sequence '() (list target)
                                               `((assign ,target (const ,exp))))))
(define let-expression '(debug (let ((x 100)) x)))
(compile-and-execute let-expression)
; testing, should be 84
(define test-expression '(begin
                             (define (double x)
                               (define something 33)
                               (define id (lambda (y) y))
                               (* 2
                                  (id x)))
                             (debug (double 42))))
; id is being looked up in the global environment, despite being
; defined in a let, which should be transformed into a lambda
(dump (caddr 
    (compile test-expression 'val 'next the-empty-environment)
))
(compile-and-execute test-expression)
