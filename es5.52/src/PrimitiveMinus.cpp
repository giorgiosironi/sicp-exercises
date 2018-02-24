#include "primitive_minus.h"
#include "cons.h"
#include "integer.h"
#include <iostream>
using namespace std;

Value* PrimitiveMinus::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = ((Integer*) argumentsCons->car())->as_int()
             - ((Integer*) argumentsCons->cadr())->as_int();
    return new Integer(result);
}

string PrimitiveMinus::to_string() const
{
    return string("PrimitiveProcedure:-");
}

