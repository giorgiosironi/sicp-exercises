#include "primitive_error.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveError::apply(List* arguments)
{
    cerr << "ERROR: " << arguments->to_string() << endl;
    exit(10);
}

string PrimitiveError::to_string() const
{
    return string("PrimitiveProcedure:error");
}

