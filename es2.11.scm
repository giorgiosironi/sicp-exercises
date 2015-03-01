; from previous exercises and the book examples
(define (make-interval a b) (cons a b))
(define (lower-bound interval)
  (min (car interval)
       (cdr interval)))
(define (upper-bound interval)
  (max (car interval)
       (cdr interval)))

; this is horrible
; I can't be sure this is correct without extensive testing
; while the previous implementation was very simple
(define (mul-interval x y)
  (let ((xl (lower-bound x))
        (xu (upper-bound x))
        (yl (lower-bound y))
        (yu (upper-bound y))
        (p1 (* (lower-bound x) (lower-bound y)))
        (p2 (* (lower-bound x) (upper-bound y)))
        (p3 (* (upper-bound x) (lower-bound y)))
        (p4 (* (upper-bound x) (upper-bound y))))
    (cond ((and (>= xl 0)
                (>= yl 0)) (make-interval (* xl
                                             yl)
                                          (* xu
                                             yu)))
          ((and (< xu 0)
                (< yu 0)) (make-interval (* xu
                                            yu)
                                         (* xl
                                            yl)))
          ((and (< xu 0)
                (>= yl 0)) (make-interval (* xl
                                             yu)
                                          (* xu
                                             yl)))
          ((and (>= xl 0)
                (< yu 0)) (make-interval (* xu
                                            yl)
                                         (* xl
                                            yu)))
          ((and (< xl 0)
                (>= xu 0)
                (>= yl 0)) (make-interval (* xl
                                             yu)
                                          (* xu
                                             yu)))
          ((and (< xl 0)
                (< yl 0)
                (>= xu 0)
                (>= yu 0)) (make-interval (min (* xu
                                                  yl)
                                               (* xl
                                                  yu))
                                          (max (* xu
                                                  yu)
                                               (* yl
                                                  xl))))
          ((and (< yl 0)
                (>= yu 0)
                (>= xl 0)) (make-interval (* xu
                                             yl)
                                          (* xu
                                             yu)))
          ((and (< xl 0)
                (>= xu 0)
                (< yu 0)) (make-interval (* xu
                                            yl)
                                         (* xl
                                            yl)))
          ((and (< yl 0)
                (>= yu 0)
                (< xu 0)) (make-interval (* xl
                                            yu)
                                         (* xl
                                            yl)))
    )))

