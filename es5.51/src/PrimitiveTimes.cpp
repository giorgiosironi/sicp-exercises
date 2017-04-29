#include "primitive_times.h"
#include "cons.h"
#include "integer.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* PrimitiveTimes::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = 1;
    while (is_pair(argumentsCons)) {
        result *= ((Integer*) argumentsCons->car())->as_int();
        argumentsCons = (Cons*) argumentsCons->cdr();
    }
    return new Integer(result);
}

string PrimitiveTimes::to_string()
{
    return string("PrimitiveProcedure:*");
}

