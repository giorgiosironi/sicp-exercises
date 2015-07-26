(define (add-streams s1 s2)
  (cons-stream (+ (stream-car s1)
                  (stream-car s2))
               (add-streams (stream-cdr s1)
                            (stream-cdr s2))))
(define (mul-streams s1 s2)
  (cons-stream (* (stream-car s1)
                  (stream-car s2))
               (mul-streams (stream-cdr s1)
                            (stream-cdr s2))))
(define ones (cons-stream 1 ones))
(define integers (cons-stream 1
                              (add-streams integers
                                           ones)))
(define factorials (cons-stream 1
                                (mul-streams factorials
                                             integers)))
