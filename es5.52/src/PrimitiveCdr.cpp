#include "primitive_cdr.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveCdr::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 1);
    List* argument = convert_to<List>(arguments->car());
    return argument->cdr();
}

string PrimitiveCdr::to_string() const
{
    return string("PrimitiveProcedure:cdr");
}
