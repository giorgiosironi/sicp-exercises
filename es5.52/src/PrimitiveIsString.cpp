#include "primitive_is_string.h"
#include "is.h"
#include "bool.h"
#include "assertion.h"
#include <iostream>
using namespace std;

Value* PrimitiveIsString::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 1, "`string?` takes 1 argument");
    Value* argument = arguments->car();
    return new Bool(is_string(argument));
}

string PrimitiveIsString::to_string() const
{
    return string("PrimitiveProcedure:string?");
}

