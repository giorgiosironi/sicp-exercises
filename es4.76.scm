; original unify-match
; p1 and p2 are two patterns such as ((? x) (? y)) or ((? x) 42)
; frame is a data structure containing bindings from variables such as x
; to values or other patterns/variables such as 42 or (? y)
; the goal is to grow the frame to accumulate in it new bindingds derived by
; unifying the two patterns
(define (unify-match p1 p2 frame)
        ; if a recurring call like the car-comparing one is made with 'failed
        ; we're finished as the match has failed given one part of the pattern
        ; is different
  (cond ((eq? frame 'failed) 'failed)
        ; if the two patterns are perfectly the same, we're finished, just return the frame
        ((equal? p1 p2) frame)
        ; if there is a variable...
        ((var? p1) (extend-if-possible p1 p2 frame))
        ((var? p2) (extend-if-possible p2 p1 frame))
        ((and (pair? p1) (pair? p2))
         ; given we are comparing lists
         ; let's match the car of the lists
         ; and then recur over their cdr
         (unify-match (cdr p1)
                      (cdr p2)
                      (unify-match (car p1)
                                   (car p2)
                                   frame)))
        (else 'failed)))
; var is a variable
; val may be data or a variable too
; frame is the usual collection of bindings
(define (extend-if-possible var val frame)
  (let ((binding (binding-in-frame var frame)))
    ; so binding is the already present binding for this variable
    (cond (binding
            (unify-match
              ; since there is already a binding, we check that its value is
              ; the same as the one proposed
              (binding-value binding) val frame))
          ((var? val)
            ; here val is a variable so we cannot do a direct check
           (let ((binding (binding-in-frame val frame)))
             ; we resolve val too in this frame and see its value
             (if binding
               ; since there is already a binding for var and val, 
               ; they must have the same value to keep this frame
               (unify-match
                 var (binding-value binding) frame)
               ; there was no binding for val, so let's extend the frame specifying it that var now must be equal to val
               (extend var val frame))))
          ;((depends-on? val var frame)
           ; ops, we got something like unification of (proc y) and y
           ; no general way to solve, refuse this scenario
          ; 'failed)
          ; it looks like there were no conflicting bindings. Let's bind var to val, it should be a value since we have reached the else
          (else (extend var val frame)))))
; primitives for manipulating frames
(define (make-binding variable value)
  (cons variable value))
(define (binding-variable binding)
  (car binding))
(define (binding-value binding)
  (cdr binding))
(define (binding-in-frame variable frame)
  (assoc variable frame))
(define (extend variable value frame)
  (cons (make-binding variable value) frame))
(define (first-binding frame)
  (car frame))
(define (rest-bindings frame)
  (cdr frame))
(define the-empty-frame '())
(define (make-var symbol)
  (cons '? symbol)) 
(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #f))
(define (var? exp)
  (tagged-list? exp '?))
; let's try compatibility...
(define (frame-compatibility f1 f2)
  (cond ((null? f1)
         f2)
        ((null? f2)
         '())
        (else
          (let ((candidate (first-binding f1)))
            (frame-compatibility (rest-bindings f1)
                                 (extend-if-possible (binding-variable candidate)
                                      (binding-value candidate)
                                      f2))))))
(define first (extend (make-var 'a) 23 (extend (make-var 'b) 42 the-empty-frame)))
(define second (extend (make-var 'c) 56 (extend (make-var 'b) 42 the-empty-frame)))
; we have values for a, b, and c
(display (frame-compatibility first second))
