(define (up-split painter n)
  (if (= 0 n)
      painter
      (let ((smaller (up-split painter (- n 1))))
           (below painter
                  (beside smaller smaller)))))
