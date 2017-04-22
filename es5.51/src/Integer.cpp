#include <string>
#include "integer.h"

Integer::Integer(int contents)
{
    this->contents = contents;
}

std::string Integer::to_string()
{
    return std::to_string(this->contents);
}

int Integer::as_int()
{
    return this->contents;
}

bool Integer::equals(const Value& other) const
{
    const Integer* other_integer = dynamic_cast<const Integer*>(&other);
    if (other_integer == NULL) {
        return false;
    }
    return this->contents == other_integer->contents;
}
