#include "primitive_apply_in_underlying_scheme.h"
#include "cons.h"
#include "symbol.h"
#include "is.h"
#include "primitive_procedure.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveApplyInUnderlyingScheme::apply(List* arguments)
{
    // TODO: assertions?
    PrimitiveProcedure* procedure = convert_to<PrimitiveProcedure>(convert_to<List>(arguments->car())->cadr());
    List* procedureArguments = (List*) arguments->cadr();
    return procedure->apply(procedureArguments);
}

string PrimitiveApplyInUnderlyingScheme::to_string() const
{
    return string("PrimitiveProcedure:apply-in-underlying-scheme");
}
