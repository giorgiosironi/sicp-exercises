#include "primitive_is_symbol.h"
#include "bool.h"
#include "symbol.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveIsSymbol::apply(List* arguments)
{
    assert_elements(arguments->to_vector(), 1, "`symbol?` takes 1 argument");
    Value* argument = arguments->car();
    return new Bool(is<Symbol>(argument));
}

string PrimitiveIsSymbol::to_string() const
{
    return string("PrimitiveProcedure:symbol?");
}

