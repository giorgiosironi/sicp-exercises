; the linear combination with a and b
; is substituted by a generic function
(define (solve-2nd f y0 dy0 dt)
  (define dy (integral (delay ddy) dy0 dt))
  (define y (integral (delay dy) y0 dt))
  (define ddy (stream-map f dy y))
  y)
