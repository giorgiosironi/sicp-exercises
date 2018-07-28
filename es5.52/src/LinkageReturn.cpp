#include "linkage.h"
#include "cons.h"

InstructionSequence* LinkageReturn::compile()
{
    return new InstructionSequence(
        vector<Symbol*>({ new Symbol("continue") }),
        vector<Symbol*>(),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("goto"),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("continue"),
                })
            })
        })
    );
}

InstructionSequence* LinkageReturn::compile_proc_appl(Symbol* target)
{
    // not implemented
}
