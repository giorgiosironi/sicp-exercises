#include "primitive_times.h"
#include "cons.h"
#include "integer.h"
#include <iostream>
using namespace std;

Value* PrimitiveTimes::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = ((Integer*) argumentsCons->car())->asInt()
             * ((Integer*) argumentsCons->cadr())->asInt();
    return new Integer(result);
}

string PrimitiveTimes::toString()
{
    return string("PrimitiveProcedure:*");
}

