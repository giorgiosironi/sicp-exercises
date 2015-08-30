; library
(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))
(define integers (integers-starting-from 1))
(define (interleave s1 s2)
  (if (stream-null? s1)
      s2
      (cons-stream (stream-car s1)
                   (interleave s2 (stream-cdr s1)))))
(define (display-line text)
  (display text)
  (newline))
(define (display-stream s number-of-elements)
  (if (> number-of-elements 0)
      (begin (display-line (stream-car s))
             (display-stream (stream-cdr s) (- number-of-elements 1)))))
; exercise
(define (weight-by-sum pair)
  (+ (car pair)
     (cadr pair)))
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
(display-line "ordered by sum")
(display-stream 
  (weighted-pairs weight-by-sum integers integers)
  10)
(define (weight-by-expression pair)
  (let ((i (car pair))
        (j (cadr pair)))
    (+ (* 2 i)
       (* 3 j)
       (* 5 i j))))
(define (divisibility-filter pair)
  (define (divisible x factor)
    (= 0 (remainder x factor)))
  (let ((i (car pair))
        (j (cadr pair)))
    (and (not (divisible i 2))
         (not (divisible i 3))
         (not (divisible i 5))
         (not (divisible j 2))
         (not (divisible j 3))
         (not (divisible j 5)))))
(display-line "not divisible by 2, 3, 5 etc.")
(display-stream 
  (stream-filter
    divisibility-filter
    (weighted-pairs weight-by-expression integers integers))
  10)
