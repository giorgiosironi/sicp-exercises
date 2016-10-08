#include "read.h"
#include "symbol.h"
#include <iostream>
#include <string>
using namespace std;

Value* Read::execute(std::vector<Value*> elements)
{
    // slightly better: consider every input a symbol
    // because we don't know yet how to parse it
    // actually it should be something like a `variable name`
    // not a symbol, because a symbol would be written as `'name`
    std::string input;
    getline(cin, input);
    return new Symbol(input);
}

std::string Read::toString()
{
    return std::string("Operation-Read");
}

