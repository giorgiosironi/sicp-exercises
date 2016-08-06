#include "bool.h"

Bool::Bool(bool value)
{
    this->value = value;
}

std::string Bool::toString()
{
    return std::string(this->value ? "#t" : "#f");
}

