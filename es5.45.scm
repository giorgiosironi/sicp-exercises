(load "chapter5.5.scm")
(load "chapter5.4.stack.scm")
(compile-and-go
  '(define (factorial n)
     (if (= n 1)
       1
       (* (factorial (- n 1)) n))))
; compiled version
;; 2
;; (total-pushes = 13 maximum-depth = 5)
;; 3
;; (total-pushes = 19 maximum-depth = 8)
;; 4
;; (total-pushes = 25 maximum-depth = 11)
;; 5
;; (total-pushes = 31 maximum-depth = 14)
;; both time and size are linear
; interpreted version
;; 2
;; (total-pushes = 45 maximum-depth = 13)
;; 3
;; (total-pushes = 80 maximum-depth = 18)
;; 4
;; (total-pushes = 112 maximum-depth = 23)
;; 5
;; (total-pushes = 144 maximum-depth = 28)
;; both time and size are linear, but larger
; compiled/interpreted ratio
;; total-pushes: 0.28-0.22
;; maximum-depth: 0.38-0.5
; special purpose machine
;; 2
;; (total-pushes = 2 maximum-depth = 2)
;; 3
;; (total-pushes = 4 maximum-depth = 4)
;; 4
;; (total-pushes = 6 maximum-depth = 6)
;; 5
;; (total-pushes = 8 maximum-depth = 8)
; special/interpreted ratio
;; total-pushes: 0.044-0.055
;; maximum-depth: 0.15-0.29
; special/compiled ratio
;; total-pushes 0.15 - 0.26
;; maximum-depth 0.4 - 0.57
; indeed the improvement for total-pushes in special/compiled is larger than for compiled/interpreted. The rate of improvement is similar for maximum-depth
;
; this is the compiled code
; COMPILED PROCEDURE: ((assign env (op compiled-procedure-env) (reg proc)) . #[compound-procedure 11])
; ((assign env (op extend-environment) (const (n)) (reg argl) (reg env)) . #[compound-procedure 12])
; ((save continue) . #[compound-procedure 13])
; ((save env) . #[compound-procedure 14])
; ((assign proc (op lookup-variable-value) (const =) (reg env)) . #[compound-procedure 15])
; ((assign val (const 1)) . #[compound-procedure 16])
; ((assign argl (op list) (reg val)) . #[compound-procedure 17])
; ((assign val (op lookup-variable-value) (const n) (reg env)) . #[compound-procedure 18])
; ((assign argl (op cons) (reg val) (reg argl)) . #[compound-procedure 19])
; ((test (op primitive-procedure?) (reg proc)) . #[compound-procedure 20])
; ((branch (label primitive-branch17)) . #[compound-procedure 21])
; ((assign continue (label after-call15)) . #[compound-procedure 22])
; ((assign val (op compiled-procedure-entry) (reg proc)) . #[compound-procedure 23])
; ((goto (reg val)) . #[compound-procedure 24])
; ((assign val (op apply-primitive-procedure) (reg proc) (reg argl)) . #[compound-procedure 25])
; ((restore env) . #[compound-procedure 26])
; ((restore continue) . #[compound-procedure 27])
; ((test (op false?) (reg val)) . #[compound-procedure 28])
; ((branch (label false-branch4)) . #[compound-procedure 29])
; ((assign val (const 1)) . #[compound-procedure 30])
; ((goto (reg continue)) . #[compound-procedure 31])
; ((assign proc (op lookup-variable-value) (const *) (reg env)) . #[compound-procedure 32])
; ((save continue) . #[compound-procedure 33])
; ((save proc) . #[compound-procedure 34])
; ((assign val (op lookup-variable-value) (const n) (reg env)) . #[compound-procedure 35])
; ((assign argl (op list) (reg val)) . #[compound-procedure 36])
; ((save argl) . #[compound-procedure 37])
; ((assign proc (op lookup-variable-value) (const factorial) (reg env)) . #[compound-procedure 38])
; ((save proc) . #[compound-procedure 39])
; ((assign proc (op lookup-variable-value) (const -) (reg env)) . #[compound-procedure 40])
; ((assign val (const 1)) . #[compound-procedure 41])
; ((assign argl (op list) (reg val)) . #[compound-procedure 42])
; ((assign val (op lookup-variable-value) (const n) (reg env)) . #[compound-procedure 43])
; ((assign argl (op cons) (reg val) (reg argl)) . #[compound-procedure 44])
; ((test (op primitive-procedure?) (reg proc)) . #[compound-procedure 45])
; ((branch (label primitive-branch8)) . #[compound-procedure 46])
; ((assign continue (label after-call6)) . #[compound-procedure 47])
; ((assign val (op compiled-procedure-entry) (reg proc)) . #[compound-procedure 48])
; ((goto (reg val)) . #[compound-procedure 49])
; ((assign val (op apply-primitive-procedure) (reg proc) (reg argl)) . #[compound-procedure 50])
; ((assign argl (op list) (reg val)) . #[compound-procedure 51])
; ((restore proc) . #[compound-procedure 52])
; ((test (op primitive-procedure?) (reg proc)) . #[compound-procedure 53])
; ((branch (label primitive-branch11)) . #[compound-procedure 54])
; ((assign continue (label after-call9)) . #[compound-procedure 55])
; ((assign val (op compiled-procedure-entry) (reg proc)) . #[compound-procedure 56])
; ((goto (reg val)) . #[compound-procedure 57])
; ((assign val (op apply-primitive-procedure) (reg proc) (reg argl)) . #[compound-procedure 58])
; ((restore argl) . #[compound-procedure 59])
; ((assign argl (op cons) (reg val) (reg argl)) . #[compound-procedure 60])
; ((restore proc) . #[compound-procedure 61])
; ((restore continue) . #[compound-procedure 62])
; ((test (op primitive-procedure?) (reg proc)) . #[compound-procedure 63])
; ((branch (label primitive-branch14)) . #[compound-procedure 64])
; ((assign val (op compiled-procedure-entry) (reg proc)) . #[compound-procedure 65])
; ((goto (reg val)) . #[compound-procedure 66])
; ((assign val (op apply-primitive-procedure) (reg proc) (reg argl)) . #[compound-procedure 67])
; ((goto (reg continue)) . #[compound-procedure 68])
; ((perform (op define-variable!) (const factorial) (reg val) (reg env)) . #[compound-procedure 69])
; ((assign val (const ok)) . #[compound-procedure 70])
; ((goto (reg continue)) . #[compound-procedure 71])
;
;
; save argl, save continue and save proc are necessary because they are overwritten with assign
; save env is necessary to keep n from being overwritten
; inlining the arithmetic operations could be an option, to avoid having to perform saves of continue and argl to call them
