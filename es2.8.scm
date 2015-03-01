; from 2.7
(define (make-interval a b) (cons a b))
(define (lower-bound interval)
  (min (car interval)
       (cdr interval)))
(define (upper-bound interval)
  (max (car interval)
       (cdr interval)))

(define (sub-interval x y)
  (make-interval (- (lower-bound x) (upper-bound y))
                 (- (upper-bound x) (lower-bound y))))
