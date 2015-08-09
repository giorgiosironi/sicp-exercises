(define (scale-stream stream factor)
  (stream-map (lambda (x) (* x factor)) stream))
(define (merge s1 s2)
  (cond ((stream-null? s1) s2)
        ((stream-null? s2) s1)
        (else
          (let ((s1car (stream-car s1))(s2car (stream-car s2)))
            (cond ((< s1car s2car)
                   (cons-stream s1car (merge (stream-cdr s1) s2)))
                  ((> s1car s2car)
                   (cons-stream s2car (merge s1 (stream-cdr s2))))
                  (else
                    (cons-stream s1car
                                 (merge (stream-cdr s1)
                                        (stream-cdr s2)))))))))
(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))
(define integers (integers-starting-from 1))
; generating stream whose elements have only 2, 3 or 5 as prime factor
; actually 1 should not be a part of this stream then... but the book says so
(define S (cons-stream 1 (merge (scale-stream S 2)
                                (merge (scale-stream S 3)
                                       (scale-stream S 5)))))
