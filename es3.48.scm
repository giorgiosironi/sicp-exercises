; if we do not access accounts in order, e.g. s1 and s2:
; P1 s1
; P2 s2
; P1 s2
; P2 s1
; deadlock
; if we keep order in all locks we acquire:
; P1 s1
; P2 s1 -- stalls and P2 s2 cannot be executed
; P1 s2 -- once P1 is finished
; P2 s2 -- now also this lock can be taken
(define (serialized-exchange account1 account2)
  (let ((serializer1 (account1 'serializer))
        (serializer2 (account2 'serializer)))
    (if (> (account2 'number)
           (account1 'number))
        ((serializer1 (serializer2 exchange))
         account1
         account2)
        ((serializer2 (serializer1 exchange))
         account1
         account2))))
