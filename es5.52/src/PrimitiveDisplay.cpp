#include "primitive_display.h"
#include "list.h"
#include "symbol.h"
#include "string.h"
#include <iostream>
using namespace std;

Value* PrimitiveDisplay::apply(List* arguments)
{
    // TODO: assert exactly 1 element in list
    cout << arguments->car()->to_string();
    return new Symbol("ok");
}

string PrimitiveDisplay::to_string() const
{
    return string("PrimitiveProcedure:display");
}

