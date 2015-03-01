; from previous exercises and the book examples
(define (make-interval a b) (cons a b))
(define (lower-bound interval)
  (min (car interval)
       (cdr interval)))
(define (upper-bound interval)
  (max (car interval)
       (cdr interval)))
(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
                   (max p1 p2 p3 p4))))

(define (div-interval x y)
  (if (spans-zero y)
      (error "Cannot span zero in an interval we are dividing for")
      (mul-interval x
                    (make-interval (/ 1.0 (upper-bound y))
                                   (/ 1.0 (lower-bound y))))))

(define (spans-zero interval)
  (>= 0
      (* (lower-bound interval)
         (upper-bound interval))))
