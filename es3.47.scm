; naive implementations from the book
(define (make-mutex)
  (let ((cell (list false)))
    (define (the-mutex m)
      (cond ((eq? m 'acquire)
             (if (test-and-set! cell)
               (the-mutex 'acquire))) ; retry
            ((eq? m 'release) (clear! cell))))
    the-mutex))
(define (clear! cell)
  (set-car! cell false))
(define (test-and-set! cell)
  (if (car cell)
    true
    (begin (set-car! cell true)
           false)))
; semaphores
(define (make-semaphore-mutex n)
  (let ((counter-mutex (make-mutex))
        (counter 0))
    (lambda (what)
      (cond ((eq? what 'acquire)
             (begin
               (counter-mutex 'acquire)
               (if (= counter
                      n)
                   (begin
                     (counter-mutex 'release)
                     #f)
                   (begin
                     (set! counter
                           (+ counter 1))
                     (counter-mutex 'release)
                     #t))))
            ((eq? what 'release)
             (begin
               (counter-mutex 'acquire)
               (set! counter
                     (- counter 1))
               (counter-mutex 'release)))))))
; I made the sempahore return #t or #f to be able to test this program without concurrency, which apparently is not implemented. Acquisition retry is on the client
(define (make-semaphore-test-and-set n)
  (define (make-cells c)
    (if (= c 0)
        '()
        (cons (list #f) (make-cells (- c 1)))))
  (define (acquire-one-cell cells)
    (if (null? cells)
        #f
        (if (test-and-set! (car cells))
            (acquire-one-cell (cdr cells))
            #t)))
  (define (release-one-cell cells)
    (if (null? cells)
        (error "Cannot find any cell to release -- RELEASE-ONE-CELL")
        (if (car (car cells))
            (set-car! (car cells) false)
            (release-once-cell (cdr cells)))))
  (let ((cells (make-cells n)))
    (define (acquire)
      (if (acquire-one-cell cells)
          #t
          (acquire)))
    (define (release)
      (release-one-cell cells))
    (lambda (what)
      (cond ((eq? what 'acquire)
             (acquire))
            ((eq? what 'release)
             (release))))))
; 1 ]=> (define s (make-semaphore-test-and-set 3))
;Value: s

; 1 ]=> (s 'acquire)
;Value: #t

; 1 ]=> (s 'acquire)
;Value: #t

; 1 ]=> (s 'acquire)
;Value: #t

; 1 ]=> (s 'acquire)
; hangs forever since no one can release a semaphore cell

