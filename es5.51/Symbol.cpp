#include <string>
#include "symbol.h"

Symbol::Symbol(std::string name)
{
    this->_name = name;
}

std::string Symbol::toString()
{
    return std::string("'") + this->_name;
}

std::string Symbol::name()
{
    return this->_name;
}
