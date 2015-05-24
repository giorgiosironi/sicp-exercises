(define (make-accumulator sum)
  (lambda (addition)
    (begin (set! sum
                 (+ sum addition))
           sum)))
