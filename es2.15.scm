
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
(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
                 (+ (upper-bound x) (upper-bound y))))
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
; Lem complaints
(define (par1 r1 r2)
  (div-interval (mul-interval r1 r2)
                (add-interval r1 r2)))
(define (par2 r1 r2)
  (let ((one (make-interval 1 1)))
    (div-interval one
                  (add-interval (div-interval one r1)
                                (div-interval one r2)))))


(define r1 (make-center-percent 100 1))
(define r2 (make-center-percent 100 1))

