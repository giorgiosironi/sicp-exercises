#include "primitive_car.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveCar::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 1);
    List* argument = convert_to<List>(arguments->car());
    return argument->car();
}

string PrimitiveCar::to_string() const
{
    return string("PrimitiveProcedure:car");
}

