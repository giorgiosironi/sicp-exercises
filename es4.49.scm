; modified parse-word
(define (parse-word word-list)
  (let ((found-word (apply amb word-list)))
    (list (car word-list) found-word)))
; not sure if we can apply to amb, it may be a language construct and not a procedure
; I have no environment to run this code
