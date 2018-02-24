#include "adjoin_arg.h"
#include "cons.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* AdjoinArg::execute(vector<Value*> elements)
{
    assert_elements(elements, 2);
    auto list = convert_to<List>(elements.at(1));
    return list->append(elements.at(0));
}

string AdjoinArg::to_string() const
{
    return string("Operation-AdjoinArg");
}

