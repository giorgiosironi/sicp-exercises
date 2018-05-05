#include <string>
#include "symbol.h"

Symbol::Symbol(const std::string name)
{
    this->_name = name;
}

std::string Symbol::to_string() const
{
    return this->_name;
}

std::string Symbol::name() const
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

ostream& operator<<(ostream& os, const ::Symbol& symbol) {
    return os << symbol.to_string();
}
