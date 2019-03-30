#include "primitive_is_pair.h"
#include "bool.h"
#include "assertion.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* PrimitiveIsPair::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 1, "`pair?` takes 1 argument");
    Value* argument = arguments->car();
    return new Bool(is_pair(argument));
}

string PrimitiveIsPair::to_string() const
{
    return string("PrimitiveProcedure:pair?");
}

