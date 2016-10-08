#include "string.h"

String::String(std::string name)
{
    this->name = name;
}

std::string String::toString()
{
    return "\"" + this->name + "\"";
}

