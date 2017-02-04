#include "cons_method_operation.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

ConsMethodOperation::ConsMethodOperation(Value* (Cons::*method_to_call)())
{
    this->method_to_call = method_to_call;
}

Value* ConsMethodOperation::execute(std::vector<Value*> elements)
{
    cout << "ConsMethodOperation" << endl;
    Cons* list = (Cons*) elements[0];
    return (*list.*(this->method_to_call))();
}

std::string ConsMethodOperation::toString()
{
    return std::string("Operation-ConsMethodOperation");
}

ConsMethodOperation* ConsMethodOperation::car()
{
    return new ConsMethodOperation(&Cons::car);
}

