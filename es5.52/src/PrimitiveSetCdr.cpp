#include "primitive_set_cdr.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveSetCdr::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 2);
    Cons* cons = convert_to<Cons>(arguments->car());
    Value* value = convert_to<Cons>(arguments->cdr());
    cons->set_cdr(value); 
}

string PrimitiveSetCdr::to_string() const
{
    return string("PrimitiveProcedure:set-cdr!");
}
