#include <iostream>
#include <stdexcept>
#include "primitive_display.h"
#include "list.h"
#include "symbol.h"
#include "string.h"
#include "length.h"
using namespace std;

Value* PrimitiveDisplay::apply(List* arguments)
{
    if (length(arguments) != 1) {
        throw std::length_error("Wrong number of arguments for `display`: " + arguments->to_string());
    }
    // TODO: assert exactly 1 element in list
    cout << arguments->car()->to_string();
    return new Symbol("ok");
}

string PrimitiveDisplay::to_string() const
{
    return string("PrimitiveProcedure:display");
}

