(define (stress-test proc)
  (for-each (lambda (iteration)
              (proc))
            (iota 1000000 1)))
; the sample let used to test 4.6 is originally executed like this:
(display (system-clock))
(stress-test
           (lambda ()
             ((lambda (x y) (+ x y)) 3 2)))
(newline)
(display (system-clock))
(newline)
; with the analyse optimization
(stress-test
           (lambda ()
             (+ 3 2)))
(display (system-clock))
(newline)
; even with this limited test, 480 ms vs 280ms which suggests analyzing may take 40% of the time in the original metacircular evaluator
