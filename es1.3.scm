(define (es13 x y z)
    (cond 
        ((and (>= y x) (>= z x)) (+ (* y y) (* z z)))
        ((and (>= x y) (>= z y)) (+ (* x x) (* z z)))
        ((and (>= y z) (>= x z)) (+ (* y y) (* x x)))))

