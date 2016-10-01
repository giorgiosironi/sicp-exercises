#include "initialize_stack.h"
#include "symbol.h"

InitializeStack::InitializeStack(Stack* stack)
{
    this->stack = stack;
}

Value* InitializeStack::execute(std::vector<Value*> elements)
{
    // do something to this->stack if needed
    return new Symbol("ok");
}

std::string InitializeStack::toString()
{
    return std::string("Operation-InitializeStack");
}

