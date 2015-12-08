; original
(rule (outranked-by ?staff-person ?boss)
      (or (supervisor ?staff-person ?boss)
          (and (supervisor ?staff-person ?middle-manager)
               (outranked-by ?middle-manager ?boss))))
; new
(rule (outranked-by ?staff-person ?boss)
      (or (supervisor ?staff-person ?boss)
          (and (outranked-by ?middle-manager ?boss)
               (supervisor ?staff-person ?middle-manager))))
; the initial unification leads us to
;     ?staff-person=(Bitdiddle Ben)
; but then the two
;     ?middle-manager
;     ?boss
; are not bound, they will loop to a new evaluation of the rule, and so on
