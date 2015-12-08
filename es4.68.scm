(rule (append-to-form () ?y ?y))
(rule (append-to-form (?u . ?v) ?y (?u . ?z))
      (append-to-form ?v ?y ?z))
(rule (reverse () ()))
(rule (reverse (?x . ?y) ?z)
      (append-to-form (reverse ?y) (?x) ?z))
; probably is able to answer only in one direction
