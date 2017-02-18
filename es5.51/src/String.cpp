#include "string.h"

String::String(std::string contents)
{
    this->contents = contents;
}

std::string String::toString()
{
    return "\"" + this->contents + "\"";
}

bool String::equals(const Value& other) const
{
    const String* other_string = dynamic_cast<const String*>(&other);
    if (other_string == NULL) {
        return false;
    }
    return this->contents == other_string->contents;
}
