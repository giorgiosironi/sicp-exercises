#include "apply_primitive_procedure.h"
#include "cons.h"
#include "primitive_procedure.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* ApplyPrimitiveProcedure::execute(vector<Value*> elements)
{
    assert_elements<Value*>(elements, 2);
    Cons* taggedProcedure = convert_to<Cons>(elements.at(0));
    PrimitiveProcedure* procedure = convert_to<PrimitiveProcedure>(taggedProcedure->cadr());
    List* arguments = convert_to<List>(elements.at(1));
    cerr << taggedProcedure->cadr()->to_string() << endl;
    auto result = procedure->apply(arguments);
    return result;
}

string ApplyPrimitiveProcedure::to_string() const
{
    return string("Operation-ApplyPrimitiveProcedure");
}

