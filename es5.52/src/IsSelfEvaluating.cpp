#include "is_self_evaluating.h"
#include "bool.h"
#include "is.h"
using namespace std;

Value* IsSelfEvaluating::execute(std::vector<Value*> elements)
{
    Value* value = elements.at(0);
    return new Bool(is_number(value) || is_string(value) || is_bool(value));
}

std::string IsSelfEvaluating::to_string() const
{
    return std::string("Operation-IsSelfEvaluating");
}

