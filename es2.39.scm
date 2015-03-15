(define (reverse-right sequence)
  (fold-right (lambda (new result) (append result (list new))) (list) sequence))
(define (reverse-left sequence)
  (fold-left (lambda (result new) (cons new result)) (list) sequence))
