; from previous exercises and the book examples
(define (make-interval a b) (cons a b))
(define (lower-bound interval)
  (min (car interval)
       (cdr interval)))
(define (upper-bound interval)
  (max (car interval)
       (cdr interval)))
(define (make-center-width c w)
  (make-interval (- c w) (+ c w)))
(define (center i)
  (/ (+ (lower-bound i) (upper-bound i)) 2))
(define (width i)
  (/ (- (upper-bound i) (lower-bound i)) 2))

(define (make-center-percent c p)
  (let ((w (* c
              (/ p
                 100))))
    (make-center-width c w)))
(define (percent interval)
  (* (/ (width interval)
        (center interval))
     100))
