#include "linkage.h"
#include "symbol.h"

InstructionSequence* Linkage::use_to_end_with(InstructionSequence* original)
{
    return original->preserving(
        std::vector<Symbol*>({ new Symbol("continue") }),
        this->compile()
    );
}
