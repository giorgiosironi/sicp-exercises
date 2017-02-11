#include "is_equal_to.h"
#include "bool.h"
#include "is.h"
using namespace std;

IsEqualTo::IsEqualTo(Value* reference)
{
    this->reference = reference;
}

Value* IsEqualTo::execute(std::vector<Value*> elements)
{
    Value* value = elements.at(0);
    return new Bool(is_eq(this->reference, value));
}

std::string IsEqualTo::toString()
{
    return std::string("Operation-IsEqualTo");
}

