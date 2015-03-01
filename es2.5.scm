(define (cons a b)
  (* (expt 2 a)
     (expt 3 b)))
(define (car pair)
  (factors 2 pair))
(define (cdr pair)
  (factors 3 pair))
(define (factors f number)
  (if (> (remainder number f)
         0)
      0
      (+ 1
         (factors f
                  (floor (/ number
                            f))))))
