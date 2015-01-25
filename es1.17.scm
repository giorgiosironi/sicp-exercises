(define (double n)
  (* n 2))
(define (halve n)
  (/ n 2))
(define (fast-times a b)
  (if (= b 1)
      a
      (fast-times (double a)
                  (halve b))))
