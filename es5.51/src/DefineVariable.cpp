#include "define_variable.h"
#include "symbol.h"
#include "value.h"
#include "environment.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* DefineVariable::execute(std::vector<Value*> elements)
{
    assert_elements(elements, 3);
    Symbol* name = convert_to<Symbol>(elements.at(0));
    Value* value = convert_to<Value>(elements.at(1));
    Environment* env = convert_to<Environment>(elements.at(2));
    env->firstFrame()->set(name, value);
    return new Symbol("ok");
}

std::string DefineVariable::toString()
{
    return std::string("Operation-DefineVariable");
}

