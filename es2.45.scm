(define (right-split painter n)
  (let ((combine (split below beside)))
    (combine painter n)))
(define (up-split painter n)
  (let ((combine (split beside below)))
    (combine painter n)))
(define (split in-proc out-proc)
  (let ((step
          (lambda (painter n recur)
            (if (= 0 n)
                painter
                (let ((smaller (recur painter (- n 1) recur)))
                     (out-proc painter
                               (in-proc smaller smaller)))))))
    (lambda (painter n)
      (step painter n step))))
