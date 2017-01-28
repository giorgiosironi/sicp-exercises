#include "bool.h"

Bool::Bool(bool value)
{
    this->value = value;
}

std::string Bool::toString()
{
    return std::string(this->value ? "#t" : "#f");
}

bool Bool::isTrue()
{
    return this->value;
}

bool Bool::isFalse()
{
    return !this->value;
}

