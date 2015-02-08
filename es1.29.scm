(define (sum term a next b)
  (if (> a b)
    0
    (+ (term a)
       (sum term (next a) next b))))
(define (integral f a b dx)
  (define (add-dx x) (+ x dx))
  (* (sum f (+ a (/ dx 2.0)) add-dx b)
     dx))
(define (simpson-rule f a b n)
  (define (h a b n)
    (/ (- b a)
       n))
  (define (term k)
    (* (f (+ a
             (* k
                (h a b n))))
       (cond ((= 0 k) 1)
             ((odd? k) 4)
             ((= n k) 1)
             ((even? k) 2))))
  (define (next k)
    (+ k
       1))
  (* (/ (h a b n)
        3)
     (sum term 0 next n)))
(define (cube x)
  (* x x x))