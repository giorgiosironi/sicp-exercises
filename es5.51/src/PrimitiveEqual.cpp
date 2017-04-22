#include "primitive_equal.h"
#include "cons.h"
#include "integer.h"
#include "bool.h"
#include <iostream>
using namespace std;

Value* PrimitiveEqual::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    bool result = ((Integer*) argumentsCons->car())->asInt()
             == ((Integer*) argumentsCons->cadr())->asInt();
    return new Bool(result);
}

string PrimitiveEqual::toString()
{
    return string("PrimitiveProcedure:=");
}

