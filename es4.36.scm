; we are using a depth-first search with amb,
; so when we enter into the first an-integer-starting-from for i and j,
; we get (1 1) as the first two number in the triple;
; when we start by choosing 1 for k, but it fails the (require).
; Then we backtrack and choose 2 for k, but it still fails. Backtracking
; leads us to choose 3, 4, 5, ... for k but we will reach infinity without
; terminating.
; This will be very inefficient but in principle it should work:
(define (an-integer-starting-from x)
  (amb x (an-integer-starting-from (+ x 1))))
(define (an-integer) (an-integer-starting-from 1))
(define (a-pythagorean-triple)
  (let ((limit (an-integer)))
    (a-pythagorean-triple-between 1 limit)))
; we would need to remove duplicates, but it's not required
