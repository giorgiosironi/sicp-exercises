#include "primitive_read.h"
#include "assertion.h"
#include "read.h"
using namespace std;

/**
 * Delegated to the Read operation, since it accomplishes the same goal of 
 * acquiring a string from input and build a s-expression
 */
Value* PrimitiveRead::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 0, "`read` takes 0 arguments");
    Read* operation = new Read();
    return operation->execute({});
}

string PrimitiveRead::to_string() const
{
    return string("PrimitiveProcedure:read");
}
