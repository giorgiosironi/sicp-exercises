#include "primitive_equal.h"
#include "cons.h"
#include "integer.h"
#include "bool.h"
#include <iostream>
using namespace std;

Value* PrimitiveEqual::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    bool result = ((Integer*) argumentsCons->car())->as_int()
             == ((Integer*) argumentsCons->cadr())->as_int();
    return new Bool(result);
}

string PrimitiveEqual::to_string() const
{
    return string("PrimitiveProcedure:=");
}

