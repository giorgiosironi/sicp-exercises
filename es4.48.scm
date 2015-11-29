(define (parse-noun)
  (parse-word nouns))
(define (parse-simple-noun-phrase)
  (define (maybe-adjective-noun)
    (amb (parse-noun noun)
         (list 'adjective-noun 
               (parse-word adjective)
               (parse-word noun))))
  (list 'simple-noun-phrase
        (parse-word articles)
        (maybe-adjective-noun)))
(define (parse-noun-phrase)
  (define (maybe-extend noun-phrase)
    (amb noun-phrase
         (maybe-extend (list 'noun-phrase
                             noun-phrase
                             (parse-prepositional-phrase)))))
  (maybe-extend (parse-simple-noun-phrase)))
