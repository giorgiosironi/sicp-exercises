(define (if-fail-former if-fail-exp)
  (cadr if-fail-exp))
(define (if-fail-latter if-fail-exp)
  (caddr if-fail-exp))
(define (analyze-if-fail exps)
  (define (sequentially-something former latter)
    (lambda (env succeed fail)
      (former env
         ;; success continuation after calling former is just the normal one
         ;; passing the value
         succeed
         ;; failure continuation for calling former is evaluating latter
         (lambda ()
           (latter env
                   ;; success continuation after calling latter is just the normal one
                   succeed
                   ;; failure continuation is the normal one
                   fail)))))
  (sequentially-something (analyze (if-fail-former if-fail-exp))
                          (analyze (if-fail-latter if-fail-exp))))
