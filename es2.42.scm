(define (queens board-size)
  (define (queen-cols k)
    (if (= k 0)
      (list empty-board)
      (filter
        (lambda (positions) (safe? k positions))
        (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))
; imported from previous exercises
(define (flatmap proc seq)
  (fold-right append (list) (map proc seq)))
(define (enumerate-interval low high)
  (if (> low high)
    (list)
    (cons low (enumerate-interval (+ low 1) high))))
; data structure
(define empty-board (list))
(define (rightest-column positions)
  (car positions))
(define (all-but-last-columns positions)
  (cdr positions))
; specific operations
(define (adjoin-position new-row k rest-of-queens)
  (cons new-row rest-of-queens))
(define (safe? k positions)
  (eq? (list)
       (filter (lambda (queen-in-conflict) (= queen-in-conflict
                                              (rightest-column positions)))
               (all-but-last-columns positions))))
