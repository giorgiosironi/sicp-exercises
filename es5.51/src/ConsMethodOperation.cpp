#include "cons_method_operation.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

ConsMethodOperation::ConsMethodOperation()
{
}

Value* ConsMethodOperation::execute(std::vector<Value*> elements)
{
    cout << "ConsMethodOperation" << endl;
    return new Bool(false);
}

std::string ConsMethodOperation::toString()
{
    return std::string("Operation-ConsMethodOperation");
}

