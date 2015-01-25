(define (cube x) (* x x x))
(define (p x) (- (* 3 x) (* 4 (cube x))))
(define (sine angle)
  (if (not (> (abs angle) 0.1))
      angle
      (p (sine (/ angle 3.0)))))

; (sine 12.15) 
; (sine 4.15)
; (sine 1.38)
; (sine 0.46)
; (sine 0.15)
; (sine 0.05)
; p is applied 5 times to the result of the last 5 calls to sine
;
; Space and number of steps are proportional to how many times we should divide by 3 to get a number < 0.1. That is O(log3(n)) which means O(log(n)).
; In the case of 12.15, (/ (log (/ 12.15 0.1)) (log 3)) => 4.36 which is ceiled to 5
