#include "extend_environment.h"
#include <vector>
#include "symbol.h"
#include "list.h"
#include "environment.h"
#include "assertion.h"
#include "conversion.h"

Value* ExtendEnvironment::execute(std::vector<Value*> elements)
{
    assert_elements(elements, 3);
    List* names = convert_to<List>(elements.at(0));
    List* values = convert_to<List>(elements.at(1));
    Environment* env = convert_to<Environment>(elements.at(2));
    std::vector<Value*> namesVector = names->toVector();
    std::vector<Symbol*> symbolsVector = std::vector<Symbol*>();
    for (int i = 0; i < namesVector.size(); i++) {
        symbolsVector.push_back(convert_to<Symbol>(
            namesVector.at(i)
        ));
    }
    return env->extend(new Frame(
        symbolsVector,
        values->toVector()
    ));
}

std::string ExtendEnvironment::toString()
{
    return std::string("Operation-ExtendEnvironment");
}

