#include "compile.h"
// temporary
#include "nil.h"
#include "cons.h"

InstructionSequence* compile(Value* exp, Symbol* target)
{
    if (is_self_evaluating(exp)) {
        return compile_self_evaluating(exp, target);
    }
    return new InstructionSequence(vector<Symbol*>(), vector<Symbol*>(), NIL);
}

bool is_self_evaluating(Value* exp)
{
    return true;
}

InstructionSequence* compile_self_evaluating(Value* exp, Symbol* target)
{
    return new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>({ target }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                target,
                Cons::from_vector({
                    new Symbol("const"),
                    exp
                })
            })
        })
    );
}
