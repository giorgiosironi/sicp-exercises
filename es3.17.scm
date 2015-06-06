(define (count-pairs x)
  (define (set-insert element set)
    (if (memq element set)
        set
        (cons element set)))
  (define (enqueue-new-elements elements seq already-seen)
    (define (not-seen? element)
      (not (memq element already-seen)))
    (let ((new-ones (filter not-seen? elements)))
      (append new-ones
              seq)))
  (define (count-pairs-iter visited queue)
    (if (null? queue)
        (length visited)
        (let ((current (car queue))
              (remaining (cdr queue)))
          (if (pair? current)
              (count-pairs-iter (set-insert current visited)
                                (enqueue-new-elements (list (car current)
                                                            (cdr current))
                                                      remaining
                                                      visited))
              (count-pairs-iter visited
                                remaining)))))
  (count-pairs-iter '() (list x)))

; tests
(define three '(a b c))
(define one-pair (cons 'b '()))
(define two-pairs (cons one-pair one-pair))
(define four (cons 'a two-pairs))
(define seven (cons two-pairs two-pairs))
(define infinite (cons 'a '()))
(set-cdr! infinite infinite)
