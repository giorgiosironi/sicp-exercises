#include "make_compiled_procedure.h"
#include "symbol.h"
#include "environment.h"
#include "cons.h"
#include "integer.h"
#include "assertion.h"
#include "conversion.h"
using namespace std;

Value* MakeCompiledProcedure::execute(vector<Value*> elements)
{
    assert_elements(elements, 2);
//    auto entry = convert_to<Symbol>(elements.at(0));
    Integer* entry = convert_to<Integer>(elements.at(0));
    auto env = convert_to<Environment>(elements.at(1));
    return Cons::from_vector({
        new Symbol("compiled-procedure"),
        entry,
        env
    });
}

string MakeCompiledProcedure::to_string() const
{
    return string("Operation-MakeCompiledProcedure");
}

