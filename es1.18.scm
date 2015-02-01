; wasn't understanding the question so I got it from
; http://www.billthelizard.com/2010/01/sicp-exercise-118-iterative.html
(define (even? n)
  (= (remainder n 2) 0))

(define (double x)
  (+ x x))

(define (halve x)
  (/ x 2))

(define (mult-iter a b p)
  (cond ((= 0 b) p)
        ((even? b) (mult-iter (double a) (halve b) p))
        (else (mult-iter a (- b 1) (+ a p)))))

(define (mult a b)
  (mult-iter a b 0))
