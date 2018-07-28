#include <stdexcept>
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
    if (*target == Symbol("val")) {
         //; target is val, last instruction of a sequence, tail recursion 
        return new InstructionSequence(
            vector<Symbol*>({
                new Symbol("proc"),
                new Symbol("continue"),
            }),
            this->all_registers(),
            Cons::from_vector({
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
                    }),
                }),
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                }),
            })
        );
    } else {
        throw std::runtime_error("Trying to compile a LinkageReturn for a non-`val` Register");
    }
}
