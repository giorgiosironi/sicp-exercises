#include "primitive_display.h"
#include "list.h"
#include "symbol.h"
#include "string.h"
#include <iostream>
using namespace std;

Value* PrimitiveDisplay::apply(List* arguments)
{
    cout << arguments->to_string() << endl;
    return new Symbol("ok");
}

string PrimitiveDisplay::to_string() const
{
    return string("PrimitiveProcedure:display");
}

