#include "user_print.h"
#include "bool.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* UserPrint::execute(std::vector<Value*> elements)
{
    cout << elements.at(0)->to_string() << endl;
}

std::string UserPrint::to_string()
{
    return std::string("Operation-UserPrint");
}

