#include "linkage.h"
#include "symbol.h"
#include "cons.h"

vector<Symbol*> Linkage::all_registers()
{
    return std::vector<Symbol*>({
        new Symbol("env"),
        new Symbol("proc"),
        new Symbol("val"),
        new Symbol("argl"),
        new Symbol("continue"),
    });
}

InstructionSequence* Linkage::use_to_end_with(InstructionSequence* original)
{
    return original->preserving(
        std::vector<Symbol*>({ new Symbol("continue") }),
        this->compile()
    );
}

InstructionSequence* Linkage::compile_proc_appl(Symbol* target)
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
                        new Symbol("TODO-should-point-to-a-label?")
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
        return InstructionSequence::empty();
    }
}
