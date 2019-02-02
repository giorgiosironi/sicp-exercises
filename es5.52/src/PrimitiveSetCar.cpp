#include "primitive_set_car.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveSetCar::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 2);
    Cons* cons = convert_to<Cons>(arguments->car());
    Value* value = convert_to<Cons>(arguments->cdr());
    cons->set_car(value); 
}

string PrimitiveSetCar::to_string() const
{
    return string("PrimitiveProcedure:set-car!");
}
