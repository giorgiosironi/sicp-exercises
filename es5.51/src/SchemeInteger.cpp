#include <string>
#include "integer.h"

Integer::Integer(int contents)
{
    this->contents = contents;
}

std::string Integer::toString()
{
    return std::to_string(this->contents);
}

int Integer::asInt()
{
    return this->contents;
}
