; library
(define (add-streams s1 s2)
  (cons-stream (+ (stream-car s1)
                  (stream-car s2))
               (add-streams (stream-cdr s1)
                            (stream-cdr s2))))
(define ones (cons-stream 1 ones))
(define integers (cons-stream 1
                              (add-streams integers
                                           ones)))
(define (stream-ref s n)
  (if (= n 0)
    (stream-car s)
    (stream-ref (stream-cdr s) (- n 1))))
; exercise
(define (repeat number)
  (cons-stream number (repeat number)))
(define (partial-sums stream)
  (cons-stream (stream-car stream)
               (add-streams (repeat (stream-car stream))
                            (partial-sums (stream-cdr stream)))))
                            
