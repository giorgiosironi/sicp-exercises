#include "initialize_stack.h"
#include "symbol.h"

Value* InitializeStack::execute(std::vector<Value*> elements)
{
    return new Symbol("ok");
}

std::string InitializeStack::toString()
{
    return std::string("Operation-InitializeStack");
}

