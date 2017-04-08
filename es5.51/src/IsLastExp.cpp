#include "is_last_exp.h"
#include "bool.h"
#include "nil.h"
#include "cons.h"
#include "is.h"
#include <iostream>
using namespace std;

Value* IsLastExp::execute(vector<Value*> elements)
{
    if (elements.size() != 1) {
        cout << "Only 1 element can be passed" << endl;
        exit(1);
    }
    auto list = dynamic_cast<Cons*>(elements.at(0));
    if (list == NULL) {
        cout << "Element must be a list" << endl;
        exit(1);
    }
    if (is_eq(list->cdr(), NIL)) {
        return new Bool(true);
    } else {
        return new Bool(false);
    }
}

string IsLastExp::toString()
{
    return string("Operation-IsLastExp");
}

