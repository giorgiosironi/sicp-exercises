(load "chapter5.2.scm")
(define ambiguous-code
  '(start
    (goto (label here))
    here
    (assign a (const 3))
    (goto (label there))
    here
    (assign a (const 4))
    (goto (label there))
    there))
(define (receive-dump insts labels)
  (display "instructions: ")
  (display insts)
  (newline)
  (display "labels: ")
  (display labels)
  (newline))
(extract-labels ambiguous-code receive-dump)
; labels: ((start ((goto (label here))) ((assign a (const 3))) ((goto (label there))) ((assign a (const 4))) ((goto (label there)))) (here ((assign a (const 3))) ((goto (label there))) ((assign a (const 4))) ((goto (label there)))) (here ((assign a (const 4))) ((goto (label there)))) (there))
; the first (here ...) shadows the second in the association list,
; so it will always assign 3

