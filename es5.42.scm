(load "es5.41.scm")
(define (compile-variable exp target linkage compile-environment)
  (end-with-linkage
    linkage
    (let ((lexical-address (find-variable exp
                                          compile-environment)))
      (if (eq? lexical-address 'not-found)
        (make-instruction-sequence '(env)
                                   (list target)
                                   `((save env)
                                     (assign env
                                             (op get-global-environment))
                                     (assign ,target
                                             (op lookup-variable-value)
                                             (const ,exp)
                                             (reg env))
                                     (restore env)))
        (make-instruction-sequence '(env)
                                   (list target)
                                   `((assign ,target
                                             (op lexical-address-lookup)
                                             (const ,lexical-address)
                                             (reg env))))))))
(define (compile-assignment exp target linkage compile-environment)
  (let* ((var (assignment-variable exp))
         (get-value-code
           (compile (assignment-value exp) 'val 'next compile-environment))
         (assignment-code 
           (let ((lexical-address (find-variable var
                                                 compile-environment)))
             (if (eq? 'not-found lexical-address)
               `((save env)
                 (assign env (op get-global-environment))
                 (perform (op set-variable-value!)
                          (const ,var)
                          (reg val)
                          (reg env))
                 (assign ,target (const ok))
                 (restore env))
               `((perform (op lexical-address-set!)
                          (const ,lexical-address)
                          (reg env)
                          (reg val))
                 (assign ,target (const ok)))))))
    (end-with-linkage linkage
                      (preserving '(env)
                                  get-value-code
                                  (make-instruction-sequence '(env val)
                                                             (list target)
                                                             assignment-code)))))
; should give 180
(define test-expression-1 '(debug (((lambda (x y)
                                      (lambda (a b c d e)
                                        ((lambda (y z) (* x y z))
                                         (* a b x)(+ c d x))))
                                    3
                                    4)
                                   1
                                   2
                                   3
                                   4
                                   5)))
(compile-and-execute test-expression-1)
; should give 10 and 42
(define test-expression-2 '(begin
                             (define a 41)
                             (debug ((lambda (x y)
                                       (set! x (+ x 1))
                                       (set! a 42)
                                       (+ x y))
                                     4
                                     5))
                             (debug a)))
(compile-and-execute test-expression-2)
