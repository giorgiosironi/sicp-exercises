; recursive version
(define (fr n)
  (if (< n 3)
      n
      (+ (fr (- n 1))
         (* 2 (fr (- n 2)))
         (* 3 (fr (- n 3))))))

; iterative version... there's a reason modern languages have for()
(define (fi n)
  (if (< n 3)
      n
      (fi-iter 0 1 2 3 n)))
(define (fi-iter a b c i n)
  (if (> i n)
      c
      (fi-iter b
               c
               (from_previous a b c)
               (+ i 1)
               n)))
(define (from_previous a b c)
      (+ c
         (* 2 b)
         (* 3 a)))
