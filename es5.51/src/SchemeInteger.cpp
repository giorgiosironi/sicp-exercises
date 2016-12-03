#include <string>
#include "scheme_integer.h"

SchemeInteger::SchemeInteger(int contents)
{
    this->contents = contents;
}

std::string SchemeInteger::toString()
{
    return std::to_string(this->contents);
}
