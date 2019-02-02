#include "primitive_cons.h"
#include "cons.h"
#include "assertion.h"
using namespace std;

Value* PrimitiveCons::apply(List* arguments)
{
    //assert_elements(arguments->to_vector(), 2, "`cons` takes 2 arguments");
    return new Cons(arguments->car(), arguments->cadr());
}

string PrimitiveCons::to_string() const
{
    return string("PrimitiveProcedure:cons");
}
