; if we do not maintain order, circuits such as the and-gate would change from this:
; 0, 1 => 0
; 1, 1 => 1 after 1 and-delay
; 1, 0 => 0 after 1 and-delay (I hope if agenda is implemented correctly)
; to this:
; 0, 1 => 0
; 1, 0 => 0 after 1 and-delay
; 1, 1 => 1 after 1 and-delay (this is an older procedure put into the queue which is however evaluated last)
