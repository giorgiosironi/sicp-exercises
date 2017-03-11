#include "primitive_plus.h"
#include "cons.h"
#include "integer.h"
#include <iostream>
using namespace std;

Value* PrimitivePlus::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = ((Integer*) argumentsCons->car())->asInt()
             + ((Integer*) argumentsCons->cadr())->asInt();
    return new Integer(result);
}

string PrimitivePlus::toString()
{
    return string("PrimitiveProcedure:+");
}

