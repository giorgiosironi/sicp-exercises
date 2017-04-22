#include "primitive_plus.h"
#include "cons.h"
#include "integer.h"
#include <iostream>
using namespace std;

Value* PrimitivePlus::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = ((Integer*) argumentsCons->car())->as_int()
             + ((Integer*) argumentsCons->cadr())->as_int();
    return new Integer(result);
}

string PrimitivePlus::to_string()
{
    return string("PrimitiveProcedure:+");
}

