#include "definition_value.h"
#include "assertion.h"
#include "conversion.h"
#include "list.h"
    #include "nil.h"
#include <iostream>
using namespace std;

Value* DefinitionValue::execute(std::vector<Value*> elements)
{
    assert_elements<Value*>(elements, 1);
    // substitute with List
    Cons* definition = convert_to<Cons>(elements.at(0));
    if (is<Symbol>(definition->cadr())) {
        return definition->caddr();
    }
    return new Cons(
        new Symbol("lambda"),
        new Cons(
            definition->cdadr(),
            definition->cddr()
        )
    );
}

std::string DefinitionValue::toString()
{
    return std::string("Operation-DefinitionValue");
}

