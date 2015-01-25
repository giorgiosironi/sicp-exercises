(define (fast-expt b n)
  (fast-expt-iter b n))

(define (fast-expt-iter b n)
  (if (= n 1)
      b 
      (fast-expt-iter (* b b)
                      (/ n 2))))

