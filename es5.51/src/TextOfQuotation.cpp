#include "text_of_quotation.h"
#include "bool.h"
#include "is.h"
#include "cons.h"
#include <iostream>
using namespace std;

Value* TextOfQuotation::execute(std::vector<Value*> elements)
{
    Cons *operand = dynamic_cast<Cons *>(elements.at(0));
    return operand->cadr();
}

std::string TextOfQuotation::toString()
{
    return std::string("Operation-TextOfQuotation");
}

