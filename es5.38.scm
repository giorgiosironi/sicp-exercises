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
