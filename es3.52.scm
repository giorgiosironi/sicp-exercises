; libraries
(define (stream-enumerate-interval low high)
  (if (> low high)
    the-empty-stream
    (cons-stream
      low
      (stream-enumerate-interval (+ low 1) high))))
(define (display-stream s)
  (stream-for-each display-line s))
(define (display-line x)
  (newline)
  (display x))
; exercise code
(define sum 0)
(define (accum x)
  (set! sum (+ x sum))
  sum)
(define seq (stream-map accum (stream-enumerate-interval 1 20)))
; here only the first element of the stream seq is evaluated, so sum is 1
(display-line "after seq")
(display-line sum)
(define y (stream-filter even? seq))
; this has forced the evaluation up to the first even element of seq,
; so we get to 6 which is the 3rd element (1 + 2 + 3)
(display-line "after y")
(display-line sum)
(define z (stream-filter (lambda (x) (= (remainder x 5) 0))
                         seq))
; this has forced evaluation up to the first element of seq which is divisible by 5
; which is 10 (1 + 2 + 3 + 4)
(display-line "after z")
(display-line sum)
(stream-ref y 7)
; given 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 66, 78, 91, 105, 120, 136
; we get to 136 (8-th element)
(display-line "after stream-ref y 7")
(display-line sum)
(display-line "display-stream z")
(display-stream z)
; this shows the whole z, and forces filter to evaluate all of seq,
; reaching 153, 171, 190, 210
(display-line "sum after display-stream z")
(display-line sum)
; if we did not implement memoization the result would be very different as accum would be evaluated multiple times for each element of the stream,
; and being stateful this would result in the first elements 1, 2, 3 and so on
; being added multiple times to sum with respect to the last ones
