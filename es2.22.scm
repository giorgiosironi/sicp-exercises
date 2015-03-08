(define (square-list items)
  (define (iter things answer)
    (if (null? things)
      answer
      (iter (cdr things)
            (cons (square (car things))
                  answer))))
  (iter items nil))

; The iterative version performs a car on `things` and cons the result of squaring the element to `answer`. `answer` can only grow on its head being a list, so
; every time we pick an element from `things` we are putting it in `answer` by growing it from bottom to top.

(define (square-list items)
  (define (iter things answer)
    (if (null? things)
      answer
      (iter (cdr things)
            (cons answer
                  (square (car things))))))
  (iter items nil))

; This does not work because we are cons-ing a list to an element, and not an element to a list. This way we get a data structure were car is used to extract the rest of the list and cdr to get the element.
