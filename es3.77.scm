(define (integral integrand initial-value dt)
  (cons-stream initial-value
               (let ((forced-integrand (force integrand)))
                 (if (stream-null? forced-integrand)
                   the-empty-stream
                   (integral (stream-cdr (delay forced-integrand))
                             (+ (* dt (stream-car forced-integrand))
                                initial-value)
                             dt)))))
