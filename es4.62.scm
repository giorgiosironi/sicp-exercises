(rule (last-pair (?x) (?x)))
(rule (last-pair (?a . ?b) (?x))
      (last-pair ?b (?x)))
; evaluating (last-pair ?x (3)) would give an infinite list of results...
