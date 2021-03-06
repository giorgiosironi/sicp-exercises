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
(define (display-line text)
  (display text)
  (newline))
(define (display-stream s number-of-elements)
  (if (> number-of-elements 0)
      (begin (display-line (stream-car s))
             (display-stream (stream-cdr s) (- number-of-elements 1)))))
(define (constant value)
  (define s
     (cons-stream value s))
  s)
(define (integral integrand initial-value dt)
  (cons-stream initial-value
               (let ((forced-integrand (force integrand)))
                 (if (stream-null? forced-integrand)
                   the-empty-stream
                   (integral (delay (stream-cdr forced-integrand))
                             (+ (* dt (stream-car forced-integrand))
                                initial-value)
                             dt)))))
; exercise
(define (RLC R L C dt)
  (lambda (vC0 iL0)
    (define vC (integral (delay dvC) vC0 dt))
    (define iL (integral (delay diL) iL0 dt))
    (define dvC (scale-stream iL (- (/ 1 C))))
    (define dIl (add-streams (scale-stream iL (- (/ R L)))
                             (scale-stream vC (/ 1 L))))
    (cons vC iL)))
(define my-circuit (RLC 1 1 0.2 0.1))
(define streams (my-circuit 10 0))
(display-stream (stream-map
                  (lambda (v i) (cons v i))
                  (car streams)
                  (cdr streams))
                40)
