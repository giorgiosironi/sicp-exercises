#include "read.h"
#include "symbol.h"
#include <iostream>
#include <string>
using namespace std;

Value* Read::execute(std::vector<Value*> elements)
{
    // just throw away the value for now 
    std::string input;
    getline(cin, input);
    return new Symbol("ok");
}

std::string Read::toString()
{
    return std::string("Operation-Read");
}

