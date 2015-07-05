(define (or-gate a1 a2 output)
  (inverter a1 'a1-not)
  (inverter a1 'a2-not)
  (and-gate 'a1-not 'a2-not 'output-not)
  (inverter 'output-not output))
; the theoretical delay is 
; (+ inverter-delay and-delay inverter-delay)
