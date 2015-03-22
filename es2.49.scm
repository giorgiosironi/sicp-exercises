(define outline
  (segments->painter (list (make-segment (make-vect 0 0)
                                         (make-vect 0 1))
                           (make-segment (make-vect 0 1)
                                         (make-vect 1 1))
                           (make-segment (make-vect 1 1)
                                         (make-vect 1 0))
                           (make-segment (make-vect 1 0)
                                         (make-vect 0 0)))))

(define x
  (segments->painter (list (make-segment (make-vect 0 0)
                                         (make-vect 1 1))
                           (make-segment (make-vect 0 1)
                                         (make-vect 1 0)))))
(define diamond
  (segments->painter (list (make-segment (make-vect 0.5 0)
                                         (make-vect 1 0.5))
                           (make-segment (make-vect 1 0.5)
                                         (make-vect 0.5 1))
                           (make-segment (make-vect 0.5 1)
                                         (make-vect 0 0.5))
                           (make-segment (make-vect 0 0.5)
                                         (make-vect 0.5 0)))))

; I would refactor most of this to poligonal->painter which takes
; a series of points to draw a closed line
; but given I can't test (no implementation for draw-line
; and hence for segments->painter) I won't break this through refactoring

(define wave
  (segments->painter (list (make-segment (make-vect 0 0.6)
                                         (make-vect 1 0.6)) ; arms
                           (make-segment (make-vect 0.5 0.6)
                                         (make-vect 0.5 0.3)) ; torso
                           (make-segment (make-vect 0.3 0)
                                         (make-vect 0.5 0.3))
                           (make-segment (make-vect 0 7.5)
                                         (make-vect 0.5 0.3)) ; legs
                           (make-segment (make-vect 0.5 0.6)
                                         (make-vect 0.4 0.8))
                           (make-segment (make-vect 0.5 0.6)
                                         (make-vect 0.6 0.8)) 
                           (make-segment (make-vect 0.5 1)
                                         (make-vect 0.4 0.8))
                           (make-segment (make-vect 0.5 1)
                                         (make-vect 0.6 0.8))))) ; head
