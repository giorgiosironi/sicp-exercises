(define (gcd a b)
  (if (= b 0)
      a
      (gcd b (remainder a b))))
(define (make-rat n d)
  (let ((g (abs (gcd n d)))
        (normalize-sign (if (< d 0)
                            -1
                            1)))
    (cons (* normalize-sign (/ n g))
          (* normalize-sign (/ d g)))))
