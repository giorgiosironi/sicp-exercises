(rule (big-shot ?p ?division)
      (and (job ?p (?division . ?))
           (not (and (supervisor ?p ?s)
                     (job ?s (?division . ?))))))
