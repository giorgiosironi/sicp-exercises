#include "primitive_is_number.h"
#include "bool.h"
#include "assertion.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* PrimitiveIsNumber::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 1, "`number?` takes 1 argument");
    Value* argument = arguments->car();
    return new Bool(is_number(argument));
}

string PrimitiveIsNumber::to_string() const
{
    return string("PrimitiveProcedure:number?");
}

