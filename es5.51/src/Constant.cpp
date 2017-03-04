#include "constant.h"

Constant::Constant(Value* constant)
{
    this->constant = constant;
}

Value* Constant::execute(std::vector<Value*> elements)
{
    return this->constant;
}

std::string Constant::toString()
{
    return "Constant: " + this->constant->toString();
}
