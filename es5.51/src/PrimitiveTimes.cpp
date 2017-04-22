#include "primitive_times.h"
#include "cons.h"
#include "integer.h"
#include <iostream>
using namespace std;

Value* PrimitiveTimes::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = ((Integer*) argumentsCons->car())->as_int()
             * ((Integer*) argumentsCons->cadr())->as_int();
    return new Integer(result);
}

string PrimitiveTimes::to_string()
{
    return string("PrimitiveProcedure:*");
}

