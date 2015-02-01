(define (fast-expt b n)
  (fast-expt-iter b n 1))

(define (even? n)
  (= 0 (remainder n 2)))

(define (fast-expt-iter b n a)
  (cond ((= n 0) a) 
        ((even? n) (fast-expt-iter (* b b)
                                   (/ n 2)
                                   a))
        (else (fast-expt-iter b
                              (- n 1)
                              (* b a)))))

