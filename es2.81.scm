; a.
; first, (get op type-tags) returns an emtpy result,
; so we have to go down and try the type coercions
; however, t1->t2 will be complex->complex
; and t2->t1 will also be complex->complex
; so we cannot find the implementation of 'exp for '(scheme-number scheme-number) and we give up

; b. with coercion from a supertype to a subtype we can't solve this problem
; as we can go from scheme-number to complex but not the other way around (in general)
; however it would be useful to define 'exp for '(complex complex) and not define it for '(scheme-number scheme-number), so the call for two arguments of type scheme-number should not fail
; Right now, if identity complex-to-complex coercions are installed, apply-generic may recur indefinitely by casting a complex to a complex and restarting a new cycle

(define (apply-generic op . args)
  (let ((type-tags (map type-tag args)))
    (let ((proc (get op type-tags)))
      (if proc
        (apply proc (map contents args))
        (if (= (length args) 2)
          (let ((type1 (car type-tags))
                (type2 (cadr type-tags))
                (a1 (car args))
                (a2 (cadr args)))
            (let ((t1->t2 (get-coercion type1 type2))
                  (t2->t1 (get-coercion type2 type1)))
              (cond ((eq? type1 type2) (error "No method for these types" (list op type-tags)))
                    (t1->t2
                      (apply-generic op (t1->t2 a1) a2))
                    (t2->t1
                      (apply-generic op a1 (t2->t1 a2)))(else
                      (error "No method for these types"
                             (list op type-tags))))))
          (error "No method for these types"
                 (list op type-tags)))))))
