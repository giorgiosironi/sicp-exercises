#include "is_not_equal_to.h"
#include "bool.h"
#include "is.h"
using namespace std;

IsNotEqualTo::IsNotEqualTo(Value* reference)
{
    this->reference = reference;
}

Value* IsNotEqualTo::execute(std::vector<Value*> elements)
{
    Value* value = elements.at(0);
    return new Bool(this->reference->to_string() != value->to_string());
}

std::string IsNotEqualTo::to_string() const
{
    return std::string("Operation-IsNotEqualTo");
}

