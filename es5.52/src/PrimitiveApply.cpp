#include "primitive_apply.h"
#include "cons.h"
#include "symbol.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* PrimitiveApply::apply(List* arguments)
{
    Value* procedure = arguments->car();
    List* procedureArguments = (List*) arguments->cdr();
    // TODO: implement call?
    return new Symbol("ok");
}

string PrimitiveApply::to_string() const
{
    return string("PrimitiveProcedure:apply");
}

