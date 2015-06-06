(define (count-pairs x)
  (if (not (pair? x))
    0
    (+ (count-pairs (car x))
       (count-pairs (cdr x))
       1)))

(define three '(a b c))

(define one-pair (cons 'b '()))
(define two-pairs (cons one-pair one-pair))
(define four (cons 'a two-pairs))

(define seven (cons two-pairs two-pairs))

(define infinite (cons 'a '()))
(set-cdr! infinite infinite)
