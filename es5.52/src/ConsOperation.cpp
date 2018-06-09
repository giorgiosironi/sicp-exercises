#include "cons_operation.h"
#include "cons.h"
#include "assertion.h"
using namespace std;

Value* ConsOperation::execute(std::vector<Value*> elements)
{
    assert_elements<Value*>(elements, 2);
    return new Cons(elements.at(0), elements.at(1));
}

std::string ConsOperation::to_string() const
{
    return std::string("Operation-Cons");
}

