; merging open code...
(load "es5.38.scm")
; with the lexical addressing extension
(load "es5.43.scm")
; but since both redefine compile, which is not very extensible, 
; we have to redefine it here merging the two versions
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
        ((primitive? exp compile-environment) (compile-primitive exp target linkage compile-environment))
        ((let? exp) (compile (let->combination exp) target linkage compile-environment))
		((application? exp)
		 (compile-application exp target linkage compile-environment))
		(else
		  (error "Unknown expression type -- COMPILE" exp))))
; also compile-primitive for 5.38 now has to accept a compile-environment additional argument
(define (compile-primitive exp target linkage compile-environment)
  (let ((op (car exp)))
    (compile-with-native op exp target linkage compile-environment)))
(define (spread-arguments operands compile-environment)
  (let ((first-operand 
         (compile (car operands) 'arg1 'next compile-environment))
        (second-operand
         (compile (cadr operands) 'arg2 'next compile-environment)))
    ; not sure what to preserve,
    ; arg1 and arg2 should work by themselves
    ; as they are 'needs' from the two blocks
    (preserving '()
                first-operand
                (preserving '(arg1)
                            second-operand
                            (make-instruction-sequence
                              '(arg1 arg2)
                              '()
                              '())))))
(define (compile-with-native op exp target linkage compile-environment)
  (let ((compiled-first-operation
         (make-instruction-sequence '(arg1 arg2)
                                    '(val arg1)
                                    `((assign val (op ,op) (reg arg1) (reg arg2))
                                      (assign arg1 (reg val)))))
        (first-2-operands (list (car (operands exp))
                                (cadr (operands exp))))
        (rest-of-operands (cddr (operands exp))))
    (from-3rd-operand (end-movement-and-linkage-decorator
                        target
                        linkage)
                      op
                      (preserving '()
                                  (spread-arguments (operands exp) compile-environment)
                                  compiled-first-operation)
                      (cddr (operands exp))
                      compile-environment)))
(define (spread-operand operand compile-environment)
  (compile operand 'arg2 'next compile-environment))
(define (from-3rd-operand end
                          op
                          partial-compilation
                          rest-of-operands
                          compile-environment)
  (if (null? rest-of-operands)
    (end partial-compilation)
    (from-3rd-operand end
                      op
                      (append-instruction-sequences partial-compilation
                                  (preserving '(arg1)
                                              (spread-operand (car rest-of-operands) compile-environment)
                                              (make-instruction-sequence '()
                                                             '()
                                                             `((assign arg1 (op ,op) (reg arg1) (reg arg2))))))
                      (cdr rest-of-operands)
                      compile-environment)))
(set! general-registers (append general-registers
                                '(arg1 arg2)))
; names of procedures are just variables pointing to their lambdas in the global environment
; primitive procedures can be redefined in nested environments however
; so it's not correct to just open code them basing on their name
; but we should look them up in the compile-environment first
; so...
; let's try to redefine primitive? so that it returns #t (and hence applies
; open coding) only if the procedure is not in the environment
(define (primitive? exp compile-environment)
  (let ((original-primitive? (lambda (exp) (and (pair? exp)
                                                (memq (car exp)
                                                      '(= + - *))))))
    (if (original-primitive? exp)
      (let ((procedure (car exp)))
        ; it it's a possible primitive,
        ; it is really so only if we don't find in nested environments
        ; (which must mean it is resolved to the one from the global environment)
        (eq? (find-variable procedure compile-environment) 'not-found))
      #f)))
(define (compile-variable exp target linkage compile-environment)
  (end-with-linkage
    linkage
    (let ((lexical-address (find-variable exp
                                          compile-environment)))
      (if (eq? lexical-address 'not-found)
        (make-instruction-sequence '(env)
                                   (list target)
                                   `((save env)
                                     (assign env
                                             (op get-global-environment))
                                     (assign ,target
                                             (op lookup-variable-value)
                                             (const ,exp)
                                             (reg env))
                                     (restore env)))
        (make-instruction-sequence '(env)
                                   (list target)
                                   `((assign ,target
                                             (op lexical-address-lookup)
                                             (const ,lexical-address)
                                             (reg env))))))))
; testing it
(define test-expression '(begin
                             (define broken-+ (lambda (x y) (+ x y 0.001)))
                             (debug ((lambda (+ a b) (+ a b))
                                     broken-+
                                     2
                                     2))))
(compile-and-execute test-expression)

