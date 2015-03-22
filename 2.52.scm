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
                                         (make-vect 0.6 0.8)) ; head
                           ; new stuff: smile
                           (make-segment (make-vect 0.45 0.8)
                                         (make-vect 0.5 0.7))
                           (make-segment (make-vect 0.55 0.8)
                                         (make-vect 0.5 0.7)))))

(define (corner-split painter n)
  (if (= n 0)
      painter
      (let ((up (up-split painter (- n 1)))
            (right (right-split painter (- n 1))))
        ; using 1 copy of up and right instead of 2
        (let ((top-left up)
              (bottom-right right)
              (corner (corner-split painter (- n 1))))
          (beside (below painter top-left)
                  (below bottom-right corner))))))

(define (square-limit painter n)
  (let ((quarter (corner-split painter n)))
    ; flipping the image on the right and on the top
    ; instead of the left and the bottom
    (let ((half (beside quarter (flip-horiz quarter))))
      (below half (flip-vert half)))))
