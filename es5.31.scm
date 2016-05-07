; explicit control evaluator attempts to evaluate a procedure application. It saves:
; - env (around operator evaluation)
; - env (around operands evaluation, except final one)
; - argl (around operands evaluation)
; - proc (around evaluation of the operand sequence)
(f 'x 'y)
; - env around operator: NOT necessary as it is looked up
;   and assigned to val
; - env around operand evaluation: NOT necessary as they
;   are places as quoted expressions in val
; - argl around operands evaluation: NOT necessary as only
;   the evaluation of another procedure would write it
; - proc around operand sequence evaluation: NOT necessary
;   as only the evaluation of another procedure would 
;   write it
((f) 'x 'y)
; - env around operator: YES necessary as evaluating (f)
;   will create a new environment
; - env around operand evaluation: NOT necessary as they
;   are places as quoted expressions in val
; - argl around operands evaluation: NOT necessary as only
;   the evaluation of another procedure would write it
; - proc around operand sequence evaluation: NOT necessary
;   as only the evaluation of another procedure would 
;   write it
(f (g 'x) y)
; - env around operator: NOT necessary as it is looked up
;   and assigned to val
; - env around operand evaluation: YES necessary as (g 'x)
;   will create a new environment
; - argl around operands evaluation: YES necessary as 
;   (g 'x) will create a new argl
; - proc around operand sequence evaluation: YES necessary
;   as (g 'x) will overwrite proc
(f (g 'x) 'y)
; - env around operator: NOT necessary as it is looked up
;   and assigned to val
; - env around operand evaluation: YES necessary as (g 'x)
;   will create a new environment
; - argl around operands evaluation: YES necessary as 
;   (g 'x) will create a new argl
; - proc around operand sequence evaluation: YES necessary
;   as (g 'x) will overwrite proc
