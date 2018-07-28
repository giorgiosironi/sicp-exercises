#include "linkage.h"
#include "symbol.h"
#include "cons.h"
#include "make_label.h"

// will need to be moved up to LinkageReturn when it implements 2 of 4 cases 
// so that the other 2 of 4 cases are implemented in LinkageLabel instead
InstructionSequence* LinkageJump::compile_proc_appl(Symbol* target)
{
    if (*target == Symbol("val")) {
        // target is val, linkage is not return, no tail recursion (it's not a tail)
        return new InstructionSequence(
            vector<Symbol*>({ new Symbol("proc") }),
            this->all_registers(),
            Cons::from_vector({
                Cons::from_vector({
                    // `((assign continue (label ,linkage))
                    new Symbol("assign"),
                    new Symbol("continue"),
                    Cons::from_vector({
                        new Symbol("label"),
                        this->_label
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("compiled-procedure-entry")
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("proc")
                    }),
                }),
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val")
                    }),
                })
            })
        );
    } else {
        Symbol* procReturn = make_label.next("proc-return");
        return new InstructionSequence(
            vector<Symbol*>({ new Symbol("proc") }),
            this->all_registers(),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("continue"),
                    Cons::from_vector({
                        new Symbol("label"),
                        procReturn
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("compiled-procedure-entry"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("proc"),
                    })
                }),
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                }),
                procReturn,
                Cons::from_vector({
                    new Symbol("assign"),
                    target,
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("label"),
                        this->_label,
                    }),
                }),
            })
        );
    }
}
