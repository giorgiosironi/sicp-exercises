#include "definition_variable.h"
#include "assertion.h"
#include "conversion.h"
#include "list.h"
#include <iostream>
using namespace std;

Value* DefinitionVariable::execute(std::vector<Value*> elements)
{
    assert_elements<Value*>(elements, 1);
    // substitute with List
    Cons* definition = convert_to<Cons>(elements.at(0));
    if (is<Symbol>(definition->cadr())) {
        return definition->cadr();
    }
    return definition->caadr();
}

std::string DefinitionVariable::to_string() const
{
    return std::string("Operation-DefinitionVariable");
}

