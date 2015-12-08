; correct version
(define (add-assertion! assertion)
  (store-assertion-in-index assertion)
  (let ((old-assertions THE-ASSERTIONS))
    (set! THE-ASSERTIONS
      (cons-stream assertion old-assertions))
    'ok))
; incorrect proposal
(define (add-assertion! assertion)
  (store-assertion-in-index assertion)
  (set! THE-ASSERTIONS
    (cons-stream assertion THE-ASSERTIONS))
  'ok)
; without the let, cons-stream woult take THE-ASSERTIONS as the pointer to the cdr of the stream, creating an infinite loop in which the stream always points to the first element and iterating on it never exits from there
