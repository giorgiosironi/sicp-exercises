#include "primitive_length.h"
#include "list.h"
#include "primitive_procedure.h"
#include "conversion.h"
#include "integer.h"
using namespace std;

Value* PrimitiveLength::apply(List* arguments)
{
    List* seq = convert_to<List>(arguments->car());
    return new Integer((seq->to_vector()).size());
}

string PrimitiveLength::to_string() const
{
    return string("PrimitiveProcedure:length");
}
