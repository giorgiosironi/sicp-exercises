#include "apply_primitive_procedure.h"
#include "cons.h"
#include "primitive_procedure.h"
#include <iostream>
using namespace std;

Value* ApplyPrimitiveProcedure::execute(vector<Value*> elements)
{
    if (elements.size() != 2) {
        cout << "Need 2 elements" << endl;
        exit(1);
    }
    Cons* taggedProcedure = dynamic_cast<Cons*>(elements.at(0));
    auto procedure = dynamic_cast<PrimitiveProcedure*>(taggedProcedure->cadr());
    auto arguments = dynamic_cast<List*>(elements.at(1));
    return procedure->apply(arguments);
}

string ApplyPrimitiveProcedure::toString()
{
    return string("Operation-ApplyPrimitiveProcedure");
}

