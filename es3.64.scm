; library
(define (average a b)
  (/ (+ a b)
     2))
(define (sqrt-improve guess x)
  (average guess (/ x guess)))
(define (sqrt-stream x)
  (define guesses
    (cons-stream 1.0
                 (stream-map (lambda (guess)
                               (sqrt-improve guess x))
                             guesses)))
  guesses)
; exercise code
(define (stream-limit stream tolerance)
  (let ((former (stream-car stream))
        (latter (stream-car (stream-cdr stream))))
    (let ((absolute-difference
           (abs (- former latter))))
      (if (< absolute-difference tolerance)
          latter
          (stream-limit (stream-cdr stream)
                        tolerance)))))
(define (sqrt x tolerance)
  (stream-limit (sqrt-stream x) tolerance))

