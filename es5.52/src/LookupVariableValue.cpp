#include "lookup_variable_value.h"
#include "environment.h"
#include "symbol.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Value* LookupVariableValue::execute(std::vector<Value*> elements)
{
    Symbol* exp = dynamic_cast<Symbol*>(elements.at(0));
    Environment* env = dynamic_cast<Environment*>(elements.at(1));
    Value* result = env->lookup(exp);
    if (result == NULL) {
        throw runtime_error("Undefined variable: " + exp->name());
    }
    return result;
}

std::string LookupVariableValue::to_string() const
{
    return std::string("Operation-LookupVariableValue");
}

