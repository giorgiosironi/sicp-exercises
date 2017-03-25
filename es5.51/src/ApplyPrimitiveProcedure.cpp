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
    cout << "elements: " << elements.at(0)->toString() << " " << elements.at(1)->toString() << endl;
    PrimitiveProcedure* procedure = convert_to<PrimitiveProcedure>(taggedProcedure->cadr());
    List* arguments = convert_to<List>(elements.at(1));
    auto result = procedure->apply(arguments);
    return result;
}

string ApplyPrimitiveProcedure::toString()
{
    return string("Operation-ApplyPrimitiveProcedure");
}

