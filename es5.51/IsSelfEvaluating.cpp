#include "is_self_evaluating.h"
#include "bool.h"
#include "is.h"
using namespace std;

Value* IsSelfEvaluating::execute(std::vector<Value*> elements)
{
    return new Bool(is_number(elements.at(0)) || is_string(elements.at(0)));
}

std::string IsSelfEvaluating::toString()
{
    return std::string("Operation-IsSelfEvaluating");
}

