#include "is_variable.h"
#include "bool.h"
#include "is.h"
using namespace std;

Value* IsVariable::execute(std::vector<Value*> elements)
{
    if (Symbol *symbol = dynamic_cast<Symbol *>(elements.at(0))) {
        return new Bool(true);
    }
    return new Bool(false);
}

std::string IsVariable::toString()
{
    return std::string("Operation-IsVariable");
}

