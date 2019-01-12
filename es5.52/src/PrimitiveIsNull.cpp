#include "primitive_is_null.h"
#include "nil.h"
#include "bool.h"
#include "assertion.h"
#include <iostream>
using namespace std;

Value* PrimitiveIsNull::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 1, "`null?` takes 1 argument");
    Value* argument = arguments->car();
    return new Bool(*argument == *NIL);
}

string PrimitiveIsNull::to_string() const
{
    return string("PrimitiveProcedure:null?");
}

