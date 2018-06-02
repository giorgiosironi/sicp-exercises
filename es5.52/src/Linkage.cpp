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

