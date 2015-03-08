(define (subsets s)
  (if (null? s)
    (list (list))
    (let ((rest (subsets (cdr s))))
      (append rest (map (lambda (x) (cons (car s) x)) rest)))))
; This is the classic mathematical recursive demonstration put into code:
; you start from ()
; and each time you add an element a:
; (), (a)
; then b
; (), (a), (b), (a,b)
