#include "primitive_eq.h"
#include "assertion.h"
#include "is.h"
#include "bool.h"
using namespace std;

Value* PrimitiveEq::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 2, "`eq?` takes 2 arguments");
    return new Bool(is_eq(arguments->car(), arguments->cadr()));
}

string PrimitiveEq::to_string() const
{
    return string("PrimitiveProcedure:eq?");
}
