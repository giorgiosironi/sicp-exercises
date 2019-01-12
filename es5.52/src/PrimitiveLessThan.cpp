#include "primitive_less_than.h"
#include "integer.h"
#include "bool.h"
#include "length.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* PrimitiveLessThan::apply(List* arguments)
{
    if (length(arguments) != 2) {
        throw std::runtime_error("Wrong length of arguments for `<`: " + arguments->to_string());
    }
    int first = convert_to<Integer>(arguments->car())->as_int();
    int second = convert_to<Integer>(arguments->cadr())->as_int();
    return new Bool(first < second);
}

string PrimitiveLessThan::to_string() const
{
    return string("PrimitiveProcedure:<");
}
