#include "primitive_plus.h"
#include "cons.h"
#include "integer.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* PrimitivePlus::apply(List* arguments)
{
    Cons* argumentsCons = (Cons*) arguments;
    int result = 0;
    while (is_pair(argumentsCons)) {
        result += ((Integer*) argumentsCons->car())->as_int();
        argumentsCons = (Cons*) argumentsCons->cdr();
    }
    return new Integer(result);
}

string PrimitivePlus::to_string()
{
    return string("PrimitiveProcedure:+");
}

