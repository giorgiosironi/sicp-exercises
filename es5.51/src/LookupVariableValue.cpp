#include "lookup_variable_value.h"
#include "environment.h"
#include "symbol.h"
#include <iostream>
using namespace std;

Value* LookupVariableValue::execute(std::vector<Value*> elements)
{
    Symbol* exp = dynamic_cast<Symbol*>(elements.at(0));
    Environment* env = dynamic_cast<Environment*>(elements.at(1));
    Value* result = env->lookup(exp);
    if (result == NULL) {
        cout << "Undefined variable: " << exp->name() << endl;
        exit(1);
    }
}

std::string LookupVariableValue::toString()
{
    return std::string("Operation-LookupVariableValue");
}

