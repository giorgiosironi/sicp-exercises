#include "is_quoted.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* IsQuoted::execute(std::vector<Value*> elements)
{
    cout << "IsQuoted" << endl;
    cout << elements.at(0)->toString() << endl;
    if (is_tagged_list(elements.at(0), new Symbol("quote"))) {
        return new Bool(true);
    }
    return new Bool(false);
}

std::string IsQuoted::toString()
{
    return std::string("Operation-IsQuoted");
}

