(define (get-record file employee-name)
  ((get 'get-record (car file)) (cdr file) employee-name))
; each file should be a pair
; - symbol 'division-a-file
; - contents
; each division must call
; (put 'get-record 'division-a 'get-record-division-a)
; with a procedure (get-record-division-a contents employee)

(define (get-salary record)
  ((get 'get-salary (car record)) (cdr record)))
; record should be a pair:
; - symbol 'division-a-record
; - contents
; each division must call
; (put 'get-salary 'division-a-record 'get-salary-division-a)
; with a procedure (get-salary-division-a contents)
; so the record must contain type information for get-salary to
; dispatch correctly

(define (find-employee-record files employee-name)
  (if (= files '())
      #f
      (let* ((current-file (car files))
             (result-on-current-file (get-record current-file employee-name)))
        (if (= result-on-current-file #f)
            (find-employee-record (cdr files))
            result-on-current-file))))

; when a new company is taken over we must install the new get-record-division-x
; and get-salary-division-x
; (put 'get-record 'division-x 'get-record-division-x)
; (put 'get-salary 'division-x-record 'get-salary-division-x)
