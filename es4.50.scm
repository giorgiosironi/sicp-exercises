; changing analyze-amb to analyze-ramb
(define (remove-ref seq index)
  (if (= index 0)
    (cdr seq)
    (cons (car seq)
          (remove-ref (cdr seq)
                      (- index 1)))))
(define (analyze-ramb exp)
  (let ((cprocs (map analyze (amb-choices exp))))
    (lambda (env succeed fail)
      (define (try-next choices)
        (let ((selected-random (random (length choices))))
          (if (null? choices)
            (fail)
            ((list-ref choices selected-random) env
                                                succeed
                                                (lambda ()
                                                  (try-next (remove-ref choices selected-random)))))))
      (try-next cprocs))))
; this can help with the generation of phrases because it avoid coing depth-first into the first possible choice of every phrase part, which may lead to very long sentences composed only by noun, noun, noun, ...
