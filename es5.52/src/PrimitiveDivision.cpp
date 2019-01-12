#include "primitive_division.h"
#include "cons.h"
#include "integer.h"
#include "is.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveDivision::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = 1;
    while (is_pair(argumentsCons)) {
        result *= convert_to<Integer>(argumentsCons->car())->as_int();
        argumentsCons = (Cons*) argumentsCons->cdr();
    }
    return new Integer(result);
}

string PrimitiveDivision::to_string() const
{
    return string("PrimitiveProcedure:/");
}

