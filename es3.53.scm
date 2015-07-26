(define (add-streams s1 s2)
  (stream-map + s1 s2))
(define s (cons-stream 1 (add-streams s s)))
; 1
; 1 + 1 = 2
; 2 + 2 = 4
; 4 + 4 = 8
