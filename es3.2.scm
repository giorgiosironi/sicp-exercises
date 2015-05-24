(define (make-monitored proc)
  (let ((calls 0))
    (lambda (input)
      (cond ((eq? 'how-many-calls? input)
             calls)
            ((eq? 'reset-count input)
             (set! calls 0))
            (else
             (begin (set! calls
                          (+ calls 1))
                    (apply proc 
                           (list input))))))))
