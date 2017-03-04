#include "is_last_operand.h"
#include "bool.h"
#include "nil.h"
#include "cons.h"
#include <iostream>
using namespace std;

Value* IsLastOperand::execute(vector<Value*> elements)
{
    cout << "IsLastOperand()" << endl;
    if (elements.size() != 1) {
        cout << "Only 1 element can be passed" << endl;
        exit(1);
    }
    if (*elements.at(0) == Nil()) {
        return new Bool(false);
    }
    auto list = dynamic_cast<Cons*>(elements.at(0));
    if (list == NULL) {
        cout << "Element must be a list" << endl;
        exit(1);
    }
    if (*list->cdr() == Nil()) {
        return new Bool(true);
    } else {
        return new Bool(false);
    }
}

string IsLastOperand::toString()
{
    return string("Operation-IsLastOperand");
}

