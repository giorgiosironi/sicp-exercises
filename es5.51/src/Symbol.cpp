#include <string>
#include "symbol.h"

Symbol::Symbol(std::string name)
{
    this->_name = name;
}

std::string Symbol::to_string()
{
    return this->_name;
}

std::string Symbol::name()
{
    return this->_name;
}

bool Symbol::equals(const Value& other) const
{
    const Symbol* other_symbol = dynamic_cast<const Symbol*>(&other);
    if (other_symbol == NULL) {
        return false;
    }
    return this->_name == other_symbol->_name;
}
