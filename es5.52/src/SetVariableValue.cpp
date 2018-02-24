#include "set_variable_value.h"
#include "symbol.h"
#include "value.h"
#include "environment.h"
#include <iostream>
using namespace std;

Value* SetVariableValue::execute(std::vector<Value*> elements)
{
    Symbol* name = dynamic_cast<Symbol *>(elements.at(0));
    Value* value = dynamic_cast<Value *>(elements.at(1));
    Environment* env = dynamic_cast<Environment *>(elements.at(2));
    env->set(name, value);
    return new Symbol("ok");
}

std::string SetVariableValue::to_string() const
{
    return std::string("Operation-SetVariableValue");
}

