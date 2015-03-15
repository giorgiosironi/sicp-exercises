(define (enumerate-interval low high)
  (if (> low high)
    (list)
    (cons low (enumerate-interval (+ low 1) high))))
(define (flatmap proc seq)
  (fold-right append (list) (map proc seq)))
(define (unique-triples n)
  (flatmap (lambda (i) (flatmap (lambda (j) (map (lambda (k) (list i j k))
                                             (enumerate-interval 1
                                                                 (- j 1))))
                            (enumerate-interval 1
                                                (- i 1))))
           (enumerate-interval 1 n)))
(define (triples-that-sum-to s n)
  (filter (lambda (triple) (= s
                              (+ (car triple)
                                 (cadr triple)
                                 (caddr triple))))
          (unique-triples n)))
