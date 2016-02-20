(load "chapter5.4.scm")
(load "chapter5.4.stack.scm")

; different primitive operations are needed
(add-primitive-procedure '= =)
(add-primitive-procedure '* *)
(add-primitive-procedure '- -)

(start eceval)

; number of pushes = 32n - 16
; maximum depth = 3 + 5n
