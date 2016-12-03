#include <iostream>
#include <string>
#include <ctype.h>
#include <boost/regex.hpp>
#include "read.h"
#include "symbol.h"
#include "scheme_integer.h"
using namespace std;


Value* Read::execute(std::vector<Value*> elements)
{
    // slightly better: consider every input a symbol
    // because we don't know yet how to parse it
    // actually it should be something like a `variable name`
    // not a symbol, because a symbol would be written as `'name`
    std::string input;
    getline(cin, input);

    boost::regex expr("[0-9]+");
    if (boost::regex_match(input, expr)) {
        return new SchemeInteger(stoi(input));
    }
    return new Symbol(input);
}

std::string Read::toString()
{
    return std::string("Operation-Read");
}

