(load "es5.40.scm")
(define (find-variable variable-name compile-environment)
  (define (find-variable-iter variable-name compile-environment current-frame)
    (if (eq? compile-environment the-empty-environment)
      'not-found
      (let* ((frame (first-frame compile-environment))
             (variables (frame-variables frame))
             (found (memq variable-name variables)))
        (if found
          (list current-frame (- (length variables)
                                 (length found)))
          (find-variable-iter variable-name
                              (enclosing-environment compile-environment)
                              (+ 1 current-frame))))))
  (find-variable-iter variable-name
                      compile-environment
                      0))
; testing it
(define sub (extend-environment '(x y) '(unassigned unassigned) the-empty-environment))
(define subsub (extend-environment '(a b c d e) '(unassigned unassigned unassigned unassigned unassigned) sub))
(define subsubsub (extend-environment '(y z) '(unassigned unassigned) subsub))
;(display (find-variable 'c subsubsub))
;(newline)
;(display (find-variable 'x subsubsub))
;(newline)
;(display (find-variable 'w subsubsub))
;(newline)
