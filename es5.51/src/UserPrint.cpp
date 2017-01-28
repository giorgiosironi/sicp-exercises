#include "user_print.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* UserPrint::execute(std::vector<Value*> elements)
{
    cout << elements.at(0) << endl;
    cout << elements.at(0)->toString() << endl;
}

std::string UserPrint::toString()
{
    return std::string("Operation-UserPrint");
}

