#include "linkage.h"

InstructionSequence* LinkageNext::compile()
{
    // correct implementation: nothing to add
    return InstructionSequence::empty();
}

Linkage* LinkageNext::lambda_linkage(Symbol* after_lambda)
{
    return new LinkageLabel(after_lambda);
}
