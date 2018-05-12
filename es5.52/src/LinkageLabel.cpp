#include "linkage.h"
#include "cons.h"

LinkageLabel::LinkageLabel(Symbol* label)
{
    this->label = label;
}

InstructionSequence* LinkageLabel::compile()
{
    return new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>(),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("goto"),
                Cons::from_vector({
                    new Symbol("label"),
                    this->label
                })
            })
        })
    );
}
