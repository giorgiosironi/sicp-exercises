#include "is_last_exp.h"
#include "bool.h"
#include "nil.h"
#include "cons.h"
#include "is.h"
#include "assertion.h"
#include "conversion.h"
#include <iostream>
using namespace std;

Value* IsLastExp::execute(vector<Value*> elements)
{
    assert_elements(elements, 1);
    auto list = convert_to<Cons>(elements.at(0));
    if (is_eq(list->cdr(), NIL)) {
        return new Bool(true);
    } else {
        return new Bool(false);
    }
}

string IsLastExp::to_string()
{
    return string("Operation-IsLastExp");
}

