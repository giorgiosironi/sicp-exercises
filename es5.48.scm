(load "chapter5.5.scm")
; define here compile-and-run, it should
; 1. compile the code
; 2. place it somewhere in the machine
; 3. execute the "compile" output which updates the global environment by adding
;    the name of the procedure and its location
; 4. return to the start of the read-eval-print-loop
(define (compile-and-run exp)
  'done)
(add-primitive-procedure 'compile-and-run compile-and-run)
(compile-and-go
  '(define (f n)
     (g n)))
