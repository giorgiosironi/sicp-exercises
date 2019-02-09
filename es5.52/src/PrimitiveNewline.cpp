#include <iostream>
#include "primitive_newline.h"
#include "assertion.h"
#include "symbol.h"
using namespace std;

Value* PrimitiveNewline::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 0, "`newline` takes 0 arguments");
    cout << endl;
    return new Symbol("ok");
}

string PrimitiveNewline::to_string() const
{
    return string("PrimitiveProcedure:newline");
}
