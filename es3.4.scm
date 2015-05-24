(define (call-the-cops)
  (display "CALLING THE COPS!")
  (newline))
(define (make-account balance password)
  (let ((incorrect-attempts 0))
    (define (withdraw amount)
      (if (>= balance amount)
        (begin (set! balance (- balance amount))
               balance)
        "Insufficient funds"))
    (define (deposit amount)
      (set! balance (+ balance amount))
      balance)
    (define (dispatch input-password m)
      (if (eq? input-password
               password)
          (begin
            (set! incorrect-attempts 0)
            (cond ((eq? m 'withdraw) withdraw)
                  ((eq? m 'deposit) deposit)
                  (else (error "Unknown request -- MAKE-ACCOUNT"
                               m))))
          (begin
            (set! incorrect-attempts
                  (+ incorrect-attempts 1))
            (if (> incorrect-attempts
                   7)
                (call-the-cops))
            (error "Incorrect password"))))
  dispatch))
