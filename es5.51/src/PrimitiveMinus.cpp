#include "primitive_minus.h"
#include "cons.h"
#include "integer.h"
#include <iostream>
using namespace std;

Value* PrimitiveMinus::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = ((Integer*) argumentsCons->car())->asInt()
             - ((Integer*) argumentsCons->cadr())->asInt();
    return new Integer(result);
}

string PrimitiveMinus::toString()
{
    return string("PrimitiveProcedure:-");
}

