(define (expand num den radix)
  (cons-stream
    (quotient (* num radix) den)
    (expand (remainder (* num radix) den) den radix)))
; produces a stream of the ciphers of the mantissa of the rational
; number corresponding to the fraction
; e.g. 1/7 is 0.142... and the stream is 1, 4, 2...
; e.g. 3/8 is 0.375 and the stream is 3, 7, 5, 0, 0, 0...
