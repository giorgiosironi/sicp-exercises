; library
(define (add-streams s1 s2)
  (cons-stream (+ (stream-car s1)
                  (stream-car s2))
               (add-streams (stream-cdr s1)
                               (stream-cdr s2))))
(define (scale-stream s n)
  (cons-stream (* (stream-car s)
                  n)
               (scale-stream (stream-cdr s)
                             n)))
(define (integral integrand initial-value dt)
  (define int
    (cons-stream initial-value
                 (add-streams (scale-stream integrand dt)
                              int)))
  int)
(define (display-line text)
  (display text)
  (newline))
(define (display-stream s number-of-elements)
  (if (> number-of-elements 0)
      (begin (display-line (stream-car s))
             (display-stream (stream-cdr s) (- number-of-elements 1)))))
; exercise
(define (constant value)
  (define s
     (cons-stream value s))
  s)
(define (RC R C dt)
  (lambda (i v0)
    (add-streams (constant v0)
                 (add-streams (scale-stream (integral i 0 dt)
                                            (/ 1 C))
                              (scale-stream i
                                            R)))))
(define RC1 (RC 5 1 0.5))
(define sample-i
  (cons-stream 1
               (scale-stream sample-i -1)))
(display-stream 
  (RC1 sample-i 10)
  20)
