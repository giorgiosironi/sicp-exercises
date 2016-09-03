#include "initialize_stack.h"
#include "symbol.h"
#include "stack.h"

Value* InitializeStack::execute(std::vector<Value*> elements)
{
    Stack* stack = new Stack();
    return new Symbol("ok");
}

std::string InitializeStack::toString()
{
    return std::string("Operation-InitializeStack");
}

