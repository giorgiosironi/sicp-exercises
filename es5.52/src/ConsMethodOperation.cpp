#include "cons_method_operation.h"
#include "bool.h"
#include "is.h"
#include "conversion.h"
#include <iostream>
#include <stdexcept>
using namespace std;

ConsMethodOperation::ConsMethodOperation(Value* (Cons::*method_to_call)())
{
    this->method_to_call = method_to_call;
}

Value* ConsMethodOperation::execute(std::vector<Value*> elements)
{
    Cons* list = convert_to<Cons>(elements[0]);
    return (*list.*(this->method_to_call))();
}

std::string ConsMethodOperation::to_string() const
{
    return std::string("Operation-ConsMethodOperation");
}

ConsMethodOperation* ConsMethodOperation::car()
{
    return new ConsMethodOperation(&Cons::car);
}

ConsMethodOperation* ConsMethodOperation::cdr()
{
    return new ConsMethodOperation(&Cons::cdr);
}

ConsMethodOperation* ConsMethodOperation::cadr()
{
    return new ConsMethodOperation(&Cons::cadr);
}

ConsMethodOperation* ConsMethodOperation::cddr()
{
    return new ConsMethodOperation(&Cons::cddr);
}

ConsMethodOperation* ConsMethodOperation::caddr()
{
    return new ConsMethodOperation(&Cons::caddr);
}

ConsMethodOperation* ConsMethodOperation::cadddr()
{
    return new ConsMethodOperation(&Cons::cadddr);
}

