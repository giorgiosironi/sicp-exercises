(load "chapter5.5.scm")
(define (spread-arguments operands)
  (let ((first-operand 
         (compile (car operands) 'arg1 'next))
        (second-operand
         (compile (cadr operands) 'arg2 'next)))
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
(define (compile-with-native op exp target linkage)
  (let ((compiled-operation
          (let ((movement-from-val
                  (if (eq? target 'val)
                    '()
                    `((assign ,target (reg val))))))
            (end-with-linkage linkage
                              (make-instruction-sequence '(arg1 arg2)
                                                         (if (eq? 'val target) '(val) `(val ,target))
                                                         (append `((assign val (op ,op) (reg arg1) (reg arg2)))
                                                                 movement-from-val))))))
    (preserving '()
                (spread-arguments (operands exp))
                compiled-operation)))
; have to rewrite compile to patch it, unfortunately it's not extensible
(define (compile exp target linkage)
  (cond ((self-evaluating? exp)
		 (compile-self-evaluating exp target linkage))
		((quoted? exp) (compile-quoted exp target linkage))
		((variable? exp)
		 (compile-variable exp target linkage))
		((assignment? exp)
		 (compile-assignment exp target linkage))
		((definition? exp)
		 (compile-definition exp target linkage))
		((if? exp) (compile-if exp target linkage))
		((lambda? exp) (compile-lambda exp target linkage))
		((begin? exp)
		 (compile-sequence (begin-actions exp)
						   target
						   linkage))
		((cond? exp) (compile (cond->if exp) target linkage))
        ((primitive? exp) (compile-primitive exp target linkage))
		((application? exp)
		 (compile-application exp target linkage))
		(else
		  (error "Unknown expression type -- COMPILE" exp))))
(define (primitive? exp)
  (and (pair? exp)
       (memq (car exp)
             '(= + - *))))
(define (compile-primitive exp target linkage)
  (let ((op (car exp)))
    (compile-with-native op exp target linkage)))
(set! general-registers (append general-registers
                                '(arg1 arg2)))
; trying it out
(define expression '(debug (* 2 (+ 3 4))))
(display "SIMPLE ARITHMETIC")
(newline)
(dump 
  (caddr (compile expression 'val 'next)))
(compile-and-execute expression)
(newline)
; on factorial
(display "FACTORIAL")
(newline)
; see how (op *) and (op +) are inlined without the overhead of a full procedure call nor the choice to be made
(define factorial '(begin
                     (define (factorial n)
                       (define (iter product counter)
                         (if (> counter n)
                           product
                           (iter (* counter product)
                                 (+ counter 1))))
                       (iter 1 1))
                     (debug (factorial 4))))
(dump 
  (caddr (compile factorial 'val 'next)))
(compile-and-execute factorial)
; extending for handling arbitrary numbers of operands
(define (end-movement-and-linkage-decorator target linkage)
  (lambda (compiled-code)
    (end-with-linkage linkage 
                      (append-instruction-sequences compiled-code
                                                    (make-instruction-sequence '(val)
                                                                               (list target)
                 `((assign ,target (reg arg1))))))))
(define (compile-with-native op exp target linkage)
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
                                  (spread-arguments (operands exp))
                                  compiled-first-operation)
                      (cddr (operands exp)))))
(define (spread-operand operand)
  (compile operand 'arg2 'next))
(define (from-3rd-operand end
                          op
                          partial-compilation
                          rest-of-operands)
  (if (null? rest-of-operands)
    (end partial-compilation)
    (from-3rd-operand end
                      op
                      (append-instruction-sequences partial-compilation
                                  (preserving '(arg1)
                                              (spread-operand (car rest-of-operands))
                                              (make-instruction-sequence '()
                                                             '()
                                                             `((assign arg1 (op ,op) (reg arg1) (reg arg2))))))
                      (cdr rest-of-operands))))
(define expression-n-arguments '(debug (* 2 3 4 5)))
(display "N-ARGUMENT ARITHMETIC")
(newline)
(dump 
  (caddr (compile expression-n-arguments 'val 'next)))
(compile-and-execute expression-n-arguments)
