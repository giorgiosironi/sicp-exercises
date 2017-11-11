#include "compile.h"
// temporary
#include "nil.h"
#include "cons.h"
#include "is.h"
#include "symbol.h"

InstructionSequence* compile(Value* exp, Symbol* target)
{
    if (is_self_evaluating(exp)) {
        return compile_self_evaluating(exp, target);
    }
    if (is_variable(exp)) {
        return new InstructionSequence(vector<Symbol*>(), vector<Symbol*>(), NIL);
    }
    return new InstructionSequence(vector<Symbol*>(), vector<Symbol*>(), NIL);
}

bool is_self_evaluating(Value* exp)
{
    return is_number(exp) || is_string(exp);
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

bool is_variable(Value* exp)
{
    if (Symbol *symbol = dynamic_cast<Symbol *>(exp)) {
        return true;
    }
    return false;
}
