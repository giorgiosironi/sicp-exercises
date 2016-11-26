#include "is_variable.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* IsVariable::execute(std::vector<Value*> elements)
{
    cout << "IsVariable" << endl;
    // this is '(reg exp), which is wrong
    cout << elements.at(0)->toString() << endl;
    if (Symbol *symbol = dynamic_cast<Symbol *>(elements.at(0))) {
        return new Bool(true);
    }
    return new Bool(false);
}

std::string IsVariable::toString()
{
    return std::string("Operation-IsVariable");
}

