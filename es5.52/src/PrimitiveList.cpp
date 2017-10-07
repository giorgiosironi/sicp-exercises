#include "primitive_list.h"
#include "cons.h"
#include "integer.h"
#include <iostream>
using namespace std;

Value* PrimitiveList::apply(List* arguments)
{
    return arguments;
}

string PrimitiveList::to_string()
{
    return string("PrimitiveProcedure:list");
}

