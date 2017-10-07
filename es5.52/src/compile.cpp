#include "compile.h"
// temporary
#include "nil.h"

InstructionSequence* compile(Value* exp, Symbol* target)
{
    return new InstructionSequence(vector<Symbol*>(), vector<Symbol*>(), NIL);
}
