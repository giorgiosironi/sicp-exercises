(load "chapter5.5.scm")
; shotgun surgery: including a compile-environment parameter
; in all compile* procedures
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
		((application? exp)
		 (compile-application exp target linkage compile-environment))
		(else
		  (error "Unknown expression type -- COMPILE" exp))))
(define (compile-self-evaluating exp target linkage compile-environment)
  (end-with-linkage linkage
                    (make-instruction-sequence '() (list target)
                                               `((assign ,target (const ,exp))))))
(define (compile-quoted exp target linkage compile-environment)
  (end-with-linkage linkage
                    (make-instruction-sequence '() (list target)
                                               `((assign ,target (const ,(text-of-quotation exp)))))))
(define (compile-variable exp target linkage compile-environment)
  (end-with-linkage linkage
                    (make-instruction-sequence '(env) (list target)
                                               `((assign ,target
                                                         (op lookup-variable-value)
                                                         (const ,exp)
                                                         (reg env))))))
(define (compile-assignment exp target linkage compile-environment)
  (let ((var (assignment-variable exp))
        (get-value-code
          (compile (assignment-value exp) 'val 'next compile-environment)))
    (end-with-linkage linkage
                      (preserving '(env)
                                  get-value-code
                                  (make-instruction-sequence '(env val) (list target)
                                                             `((perform (op set-variable-value!)
                                                                        (const ,var)
                                                                        (reg val)
                                                                        (reg env))
                                                               (assign ,target (const ok))))))))
(define (compile-definition exp target linkage compile-environment)
  (let ((var (definition-variable exp))
        (get-value-code
          (compile (definition-value exp) 'val 'next compile-environment)))
    (end-with-linkage linkage
                      (preserving '(env)
                                  get-value-code
                                  (make-instruction-sequence '(env val) (list target)
                                                             `((perform (op define-variable!)
                                                                        (const ,var)
                                                                        (reg val)
                                                                        (reg env))
                                                               (assign ,target (const ok))))))))

(define (compile-if exp target linkage compile-environment)
  (let ((t-branch (make-label 'true-branch))
        (f-branch (make-label 'false-branch))
        (after-if (make-label 'after-if)))
    (let ((consequent-linkage
            (if (eq? linkage 'next) after-if linkage)))
      (let ((p-code (compile (if-predicate exp)
                             'val 
                             'next
                             compile-environment))
            (c-code
              (compile
                (if-consequent exp)
                target
                consequent-linkage 
                compile-environment))
            (a-code
              (compile 
                (if-alternative exp)
                target
                linkage
                compile-environment)))
        (preserving '(env continue)
                    p-code
                    (append-instruction-sequences
                      (make-instruction-sequence '(val) '()
                                                 `((test (op false?) (reg val))
                                                   (branch (label ,f-branch))))
                      (parallel-instruction-sequences
                        (append-instruction-sequences t-branch c-code)
                        (append-instruction-sequences f-branch a-code))
                      after-if))))))
(define (compile-sequence seq target linkage compile-environment)
  (if (last-exp? seq)
    (compile (first-exp seq) target linkage compile-environment)
    (preserving '(env continue)
                (compile (first-exp seq) target 'next compile-environment)
                (compile-sequence (rest-exps seq) target linkage compile-environment))))
(define (compile-lambda exp target linkage compile-environment)
  (let ((proc-entry (make-label 'entry))
        (after-lambda (make-label 'after-lambda)))
    (let ((lambda-linkage
            (if (eq? linkage 'next) after-lambda linkage)))
      (append-instruction-sequences
        (tack-on-instruction-sequence
          (end-with-linkage lambda-linkage
                            (make-instruction-sequence '(env) (list target)
                                                       `((assign ,target
                                                                 (op make-compiled-procedure)
                                                                 (label ,proc-entry)
                                                                 (reg env)))))
          (compile-lambda-body exp proc-entry compile-environment))
        after-lambda))))
(define (compile-lambda-body exp proc-entry compile-environment)
  (define (many-unassigned another-list)
    (if (null? another-list)
      '()
      (cons 'unassigned (many-unassigned (cdr another-list)))))
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
      (compile-sequence (lambda-body exp)
                        'val
                        'return 
                        extended-environment))))
(define (compile-application exp target linkage compile-environment)
  (let ((proc-code (compile (operator exp) 'proc 'next compile-environment))
        (operand-codes
          (map (lambda (operand)
                 (compile operand 'val 'next compile-environment))
               (operands exp))))
    (preserving '(env continue)
                proc-code
                (preserving '(proc continue)
                            (construct-arglist operand-codes)
                            (compile-procedure-call target linkage compile-environment)))))

(define (compile-procedure-call target linkage compile-environment)
  (let ((primitive-branch (make-label 'primitive-branch))
        (compiled-branch (make-label 'compiled-branch))
        (after-call (make-label 'after-call)))
    (let ((compiled-linkage
            (if (eq? linkage 'next) after-call linkage)))
      (append-instruction-sequences
        (make-instruction-sequence '(proc) '()`((test (op primitive-procedure?) (reg proc))
                                                (branch (label ,primitive-branch))))
        (parallel-instruction-sequences
          (append-instruction-sequences
            compiled-branch
            (compile-proc-appl target compiled-linkage compile-environment))
          (append-instruction-sequences
            primitive-branch
            (end-with-linkage linkage
                              (make-instruction-sequence '(proc argl)
                                                         (list target)
                                                         `((assign ,target
                                                                   (op apply-primitive-procedure)
                                                                   (reg proc)
                                                                   (reg argl)))))))
        after-call))))
(define (compile-proc-appl target linkage compile-environment)
  (cond ((and (eq? target 'val) (not (eq? linkage 'return)))
         ; target is val, linkage is not return, no tail recursion (it's not a tail)
         (make-instruction-sequence '(proc) all-regs
                                    `((assign continue (label ,linkage))
                                      (assign val (op compiled-procedure-entry)
                                              (reg proc))
                                      (goto (reg val)))))
        ((and (not (eq? target 'val))
              (not (eq? linkage 'return)))
         ; target is not val, linkage is not return, still no tail recursion
         (let ((proc-return (make-label 'proc-return)))
           (make-instruction-sequence '(proc) all-regs
                                      `((assign continue (label ,proc-return))
                                        (assign val (op compiled-procedure-entry)
                                                (reg proc))
                                        (goto (reg val))
                                        ,proc-return
                                        (assign ,target (reg val))
                                        (goto (label ,linkage))))))
        ((and (eq? target 'val) (eq? linkage 'return))
         ; target is val, last instruction of a sequence, tail recursion 
         (make-instruction-sequence '(proc continue) all-regs
                                    '((assign val (op compiled-procedure-entry)
                                              (reg proc))
                                      (goto (reg val)))))
        ((and (not (eq? target 'val)) (eq? linkage 'return))
         ; why are you writing in something different from val
         ; when you are then immediately returning and losing it?
         (error "return linkage, target not val -- COMPILE"
                target))))
(define expression '(begin (define (id x) x) (id 42)))
(dump (caddr (compile expression 'val 'next the-empty-environment)))
