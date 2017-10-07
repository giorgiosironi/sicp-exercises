#include "is_last_operand.h"
#include "bool.h"
#include "nil.h"
#include "cons.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* IsLastOperand::execute(vector<Value*> elements)
{
    assert_elements(elements, 1);
    if (*elements.at(0) == Nil()) {
        return new Bool(false);
    }
    auto list = convert_to<Cons>(elements.at(0));
    if (*list->cdr() == Nil()) {
        return new Bool(true);
    } else {
        return new Bool(false);
    }
}

string IsLastOperand::to_string()
{
    return string("Operation-IsLastOperand");
}

