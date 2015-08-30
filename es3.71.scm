; library
(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))
(define integers (integers-starting-from 1))
(define (display-line text)
  (display text)
  (newline))
(define (display-stream s number-of-elements)
  (if (> number-of-elements 0)
      (begin (display-line (stream-car s))
             (display-stream (stream-cdr s) (- number-of-elements 1)))))
(define (merge-weighted weight s1 s2)
  (cond ((stream-null? s1) s2)
        ((stream-null? s2) s1)
        (else
          (let ((s1car (stream-car s1))(s2car (stream-car s2)))
            (cond ((< (weight s1car)
                      (weight s2car))
                   (cons-stream s1car (merge-weighted weight
                                                      (stream-cdr s1)
                                                      s2)))
                  (else
                   (cons-stream s2car (merge-weighted weight
                                                      s1 
                                                      (stream-cdr s2)))))))))
(define (weighted-pairs weight s t)
  (cons-stream
    (list (stream-car s) (stream-car t))
    (merge-weighted
      weight
      (stream-map (lambda (x) (list (stream-car s) x))
                  (stream-cdr t))
      (weighted-pairs weight (stream-cdr s) (stream-cdr t)))))
; exercise
(define (weight-by-cubes pair)
  (let ((i (car pair))
        (j (cadr pair)))
    (+ (expt i 3)
       (expt j 3))))
(define stream (weighted-pairs weight-by-cubes integers integers))
(display-stream stream 10)
(define (search-stream-for-ramanujan stream)
    (let ((first (stream-car stream))
          (second (stream-car (stream-cdr stream))))
      (if (equal? (weight-by-cubes first)
                  (weight-by-cubes second))
          (cons-stream 
            (list first second (weight-by-cubes first))
            (search-stream-for-ramanujan (stream-cdr stream)))
          (search-stream-for-ramanujan (stream-cdr stream)))))
(display-line "Ramanujan numbers stream")
(display-stream (search-stream-for-ramanujan stream) 6)
