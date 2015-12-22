; Box-and-pointer representation
; x --> [ ... ... ]
;          |   |
;          1   2
; y --> [ ... ... ] -- [ ... nil ]
;          |              |
;       [ ... ... ] <-----|
;          |   |
;          1   2
; 
; Memory representation
; the-cars n1 p1 p1
; the-cdrs n2 eo p2
; free: p4
; x: p1
; y: p3
