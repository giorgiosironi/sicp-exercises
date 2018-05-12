(load "chapter5.2.scm")
(load "chapter5.scm")
(load "chapter5.4.scm")
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
		((application? exp)
		 (compile-application exp target linkage))
		(else
		  (error "Unknown expression type -- COMPILE" exp))))
; append-instruction-sequence: just appends together
; preserving: appends seq1 and seq2 but wraps around seq1 stack save/restore operations for the registers used by seq2
(define (make-instruction-sequence needs modifies statements)
  (list needs modifies statements))
(define (empty-instruction-sequence)
  (make-instruction-sequence '() '() '()))
; each code generator will end with a linkage:
; - return (from a procedure application)
; - next (just go on)
; - goto (a label)
(define (compile-linkage linkage)
  (cond ((eq? linkage 'return)
         (make-instruction-sequence '(continue) '()
                                    '((goto (reg continue)))))
        ((eq? linkage 'next)
         (empty-instruction-sequence))
        (else
          (make-instruction-sequence '() '()
                                     `((goto (label ,linkage)))))))
; the linkage code will be joined in two instructions
; by preserving continue, which is needed in case of 'return
(define (end-with-linkage linkage instruction-sequence)
  (preserving '(continue)
              instruction-sequence
              (compile-linkage linkage)))
; compiling simple expressions:
; - they all modify target
; - looking upvariables requires env
(define (compile-self-evaluating exp target linkage)
  (end-with-linkage linkage
                    (make-instruction-sequence '() (list target)
                                               `((assign ,target (const ,exp))))))
(define (compile-quoted exp target linkage)
  (end-with-linkage linkage
                    (make-instruction-sequence '() (list target)
                                               `((assign ,target (const ,(text-of-quotation exp)))))))
(define (compile-variable exp target linkage)
  (end-with-linkage linkage
                    (make-instruction-sequence '(env) (list target)
                                               `((assign ,target
                                                         (op lookup-variable-value)
                                                         (const ,exp)
                                                         (reg env))))))
; assignments and definitions are recursive:
; - generate code that computes the value
; - assign it to the target
(define (compile-assignment exp target linkage)
  (let ((var (assignment-variable exp))
        (get-value-code
          (compile (assignment-value exp) 'val 'next)))
    (end-with-linkage linkage
                      (preserving '(env)
                                  get-value-code
                                  (make-instruction-sequence '(env val) (list target)
                                                             `((perform (op set-variable-value!)
                                                                        (const ,var)
                                                                        (reg val)
                                                                        (reg env))
                                                               (assign ,target (const ok))))))))
(define (compile-definition exp target linkage)
  (let ((var (definition-variable exp))
        (get-value-code
          (compile (definition-value exp) 'val 'next)))
    (end-with-linkage linkage
                      (preserving '(env)
                                  get-value-code
                                  (make-instruction-sequence '(env val) (list target)
                                                             `((perform (op define-variable!)
                                                                        (const ,var)
                                                                        (reg val)
                                                                        (reg env))
                                                               (assign ,target (const ok))))))))
; conditionals. Notice if predicate then consequent else alternative
; notice how consequent is linked to after-if to skip
; over the alternative
; env and continue are preserved when evaluating the 
; predicate, as they can be used by branches
(define label-counter 0)
(define (new-label-number)
  (set! label-counter (+ 1 label-counter))
  label-counter)
(define (make-label name)
  (string->symbol
    (string-append (symbol->string name)
                   (number->string (new-label-number)))))
(define (compile-if exp target linkage)
  (let ((t-branch (make-label 'true-branch))
        (f-branch (make-label 'false-branch))
        (after-if (make-label 'after-if)))
    (let ((consequent-linkage
            (if (eq? linkage 'next) after-if linkage)))
      (let ((p-code (compile (if-predicate exp)
                             'val 
                             'next))
            (c-code
              (compile
                (if-consequent exp)
                target
                consequent-linkage))
            (a-code
              (compile 
                (if-alternative exp)
                target
                linkage)))
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
; sequences of statements
; they are joined to each other with 'next linkages
; but they need to preserve env (for the following ones)
; and continue (possibly for the last linkage)
(define (compile-sequence seq target linkage)
  (if (last-exp? seq)
    (compile (first-exp seq) target linkage)
    (preserving '(env continue)
                (compile (first-exp seq) target 'next)
                (compile-sequence (rest-exps seq) target linkage))))
; lambda expressions: code is inserted here but not immediately executed
; if the linkage is next, we'll skip over it
; notice that the lambda is tacked on, which means
; it's not part of the normal sequence of statements
(define (compile-lambda exp target linkage)
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
          (compile-lambda-body exp proc-entry))
        after-lambda))))
; compiling the lambda body
; the new environment is augmented with the formal parameters
; but the body in itself is just compiled as a sequence
(define (compile-lambda-body exp proc-entry)
  (let ((formals (lambda-parameters exp)))
    (append-instruction-sequences
      (make-instruction-sequence '(env proc argl) '(env)
                                 `(,proc-entry
                                    (assign env (op compiled-procedure-env) (reg proc))
                                    (assign env
                                            (op extend-environment)
                                            (const ,formals)
                                            (reg argl)
                                            (reg env))))
      (compile-sequence (lambda-body exp) 'val 'return))))
; the application consists of evaluating operator and operands first, but connecting them together while preserving respectively env and proc
(define (compile-application exp target linkage)
  (let ((proc-code (compile (operator exp) 'proc 'next))
        (operand-codes
          (map (lambda (operand)
                 (compile operand 'val 'next))
               (operands exp))))
    (preserving '(env continue)
                proc-code
                (preserving '(proc continue)
                            (construct-arglist operand-codes)
                            (compile-procedure-call target linkage)))))
; building the argument list from last to first, with cons
(define (construct-arglist operand-codes)
  (let ((operand-codes (reverse operand-codes)))
    (if (null? operand-codes)
      ; 0-argument case
      (make-instruction-sequence '() '(argl)
                                 '((assign argl (const ()))))
      (let ((code-to-get-last-arg
              (append-instruction-sequences
                (car operand-codes)
                (make-instruction-sequence '(val) '(argl)
                                           '((assign argl (op list) (reg val)))))))
        (if (null? (cdr operand-codes))
          ; 1-argument case
          code-to-get-last-arg
          (preserving '(env)
                      code-to-get-last-arg
                      (code-to-get-rest-args
                        (cdr operand-codes))))))))
; building all the arguments different from the last
(define (code-to-get-rest-args operand-codes)
  (let ((code-for-next-arg
          (preserving '(argl)
                      (car operand-codes)
                      (make-instruction-sequence '(val argl) '(argl)
                                                 '((assign argl
                                                           (op cons) (reg val) (reg argl)))))))
    (if (null? (cdr operand-codes))
      code-for-next-arg
      (preserving '(env)
                  code-for-next-arg
                  (code-to-get-rest-args (cdr operand-codes))))))
; compiling the procedure call, either to a primitive or compiled procedure
; the primitive branch is directly specified here
(define (compile-procedure-call target linkage)
  (let ((primitive-branch (make-label 'primitive-branch))
        (compiled-branch (make-label 'compiled-branch))
        (after-call (make-label 'after-call)))
    (let ((compiled-linkage
            (if (eq? linkage 'next) after-call linkage)))
      (append-instruction-sequences
        (make-instruction-sequence '(proc) '()`((test (op primitive-procedure?) (reg proc))
                                                (branch (label ,primitive-branch))))
        ; parallel because they won't be executed sequentially
        (parallel-instruction-sequences
          (append-instruction-sequences
            compiled-branch
            (compile-proc-appl target compiled-linkage))
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
; compiled procedure application
(define all-regs '(env proc val argl continue))
(define (compile-proc-appl target linkage)
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
; building instruction sequence data structure
;; selectors
(define (registers-needed s)
  (if (symbol? s) '() (car s)))
(define (registers-modified s)
  (if (symbol? s) '() (cadr s)))
(define (statements s)
  (if (symbol? s) (list s) (caddr s)))
;; predicates
(define (needs-register? seq reg)
  (memq reg (registers-needed seq)))
(define (modifies-register? seq reg)
  (memq reg (registers-modified seq)))
; appending arbitrary number of sequences
(define (append-instruction-sequences . seqs)
  (define (append-2-sequences seq1 seq2)
    (make-instruction-sequence
      ; registers needed by the combined sequence
      (list-union (registers-needed seq1)
                  (list-difference (registers-needed seq2)
                                   (registers-modified seq1)))
      ; registers modified by the combined sequence
      (list-union (registers-modified seq1)
                  (registers-modified seq2))
      (append (statements seq1) (statements seq2))))
  (define (append-seq-list seqs)
    (if (null? seqs)
      (empty-instruction-sequence)
      (append-2-sequences (car seqs)
                          (append-seq-list (cdr seqs)))))
  (append-seq-list seqs))
;; set operations needed by append-instruction-sequences
(define (list-union s1 s2)
  (cond ((null? s1) s2)
        ((memq (car s1) s2) (list-union (cdr s1) s2))
        (else (cons (car s1) (list-union (cdr s1) s2)))))
(define (list-difference s1 s2)
  (cond ((null? s1) '())
        ((memq (car s1) s2) (list-difference (cdr s1) s2))
        (else (cons (car s1)
                    (list-difference (cdr s1) s2)))))
; preserving registers while combining two sequences
;; recursive over regs
(define (preserving regs seq1 seq2)
  (if (null? regs)
    (append-instruction-sequences seq1 seq2)
    (let ((first-reg (car regs)))
      (if (and (needs-register? seq2 first-reg)
               (modifies-register? seq1 first-reg))
        (preserving (cdr regs)
                    (make-instruction-sequence
                      (list-union (list first-reg)
                                  (registers-needed seq1))
                      (list-difference (registers-modified seq1)
                                       (list first-reg))
                      (append `((save ,first-reg))
                              (statements seq1)
                              `((restore ,first-reg))))
                    seq2)
        (preserving (cdr regs) seq1 seq2)))))
; simply putting code segments closed to each other
;; body-seq should be unreachable from seq, like a closure body put there for convenience
(define (tack-on-instruction-sequence seq body-seq)
  (make-instruction-sequence
    (registers-needed seq)
    (registers-modified seq)
    (append (statements seq) (statements body-seq))))
; any of seq1 and seq2 may be executed
(define (parallel-instruction-sequences seq1 seq2)
  (make-instruction-sequence
    (list-union (registers-needed seq1)
                (registers-needed seq2))
    (list-union (registers-modified seq1)
                (registers-modified seq2))
    (append (statements seq1) (statements seq2))))
; missing compiled procedure data structure (from note 38)
(define (make-compiled-procedure entry env)
  ;(display "COMPILED PROCEDURE (without labels): ")
  ;(dump entry)
  ;(newline)
  (list 'compiled-procedure entry env))
(define (compiled-procedure? proc)
  (tagged-list? proc 'compiled-procedure))
(define (compiled-procedure-entry c-proc) (cadr c-proc))
(define (compiled-procedure-env c-proc) (caddr c-proc))
; operations necessary for the machine to execute compiled code
(add-operation 'make-compiled-procedure make-compiled-procedure)
(add-operation 'compiled-procedure-env compiled-procedure-env)
(add-operation 'compiled-procedure-entry compiled-procedure-entry)
(add-operation 'compiled-procedure? compiled-procedure?)
(add-operation 'list list)
(add-operation 'cons cons)
(add-operation '+ +)
(add-operation '- -)
(add-operation '* *)
(add-operation 'false? false?)
; utility for dumping
(define (dump machine-instructions)
  (map (lambda (inst) 
         (display inst)
         (newline))
       machine-instructions))
(add-primitive-procedure 'debug (lambda (arg)
                        (display "DEBUG: ")
                        (display arg)
                        (newline)))
(add-primitive-procedure '> >)
(add-primitive-procedure '< <)
(add-primitive-procedure '* *)
(add-primitive-procedure '= =)
(add-primitive-procedure '+ +)
(add-primitive-procedure '- -)

(define general-registers eceval-registers)
; my brutal way to execute a compiled procedure
(define (compile-and-execute expression)
  (let* ((compiled-program (caddr (compile expression 'val 'next)))
         (linked-program (append
                           '(
                             (perform (op initialize-stack))
                             (assign env (op get-global-environment))
                           )
                           compiled-program))
         (machine-of-compiled-program (make-machine general-registers
                               machine-operations
                               linked-program)))
    (display "Compiled a ")
    (display (length compiled-program))
    (display "-instruction program. Now starting it...")
    (newline)
    (start machine-of-compiled-program)))
; the book's way of executing compiled procedures interfacing them
; also with primitive and compound ones
(define compiled-procedures-patch 
  '(compiled-procedures-patch-start
    apply-dispatch
    (test (op primitive-procedure?) (reg proc))
    (branch (label primitive-apply))
    (test (op compound-procedure?) (reg proc))
    (branch (label compound-apply))
    (test (op compiled-procedure?) (reg proc))
    (branch (label compiled-apply))
    (goto (label unknown-procedure-type))
    compiled-apply
    (restore continue)
    (assign val (op compiled-procedure-entry) (reg proc))
    (goto (reg val))
    compiled-procedures-patch-end))
(apply-patch compiled-procedures-patch
             'apply-dispatch)
(define external-entry-patch
  '(external-entry
    (perform (op initialize-stack))
    (assign env (op get-global-environment))
    ; uncomment to see what gets executed during initial compilation
    ; basically code constructing the compiled procedure
    ; and modifying the global environment to expose it
    ; (perform (op dump) (reg val))
    (assign continue (label print-result))
    (goto (reg val))
    external-entry-patch-end))
(apply-patch external-entry-patch
             'end-of-machine)
; the order with which we apply the patches is important:
; this one refers to the label external-entry so it should come last
(define start-of-machine-with-compile-code-patch
  '(start-of-machine-with-compile-code-patch-start
    (branch (label external-entry))
    start-of-machine-with-compile-code-patch-end))
(apply-patch start-of-machine-with-compile-code-patch
             'start-of-machine)
; WE NEED to apply the stack measurements patches too
; put the compiled code of the procedure in val, and go executing it
; by using the special external-entry label
; instead of entering the read-eval-print-loop,
; where we will go once it's compiled
(define (compile-and-go expression)
  (let ((instructions
          (assemble (statements
                      (compile expression 'val 'return))
                    eceval)))
    (set! the-global-environment (setup-environment))
    (set-register-contents! eceval 'val instructions)
    (set-register-contents! eceval 'flag true)
    (start eceval)))
(define (start-machine)
  (compile-and-go '(define nothing 'nothing)))
