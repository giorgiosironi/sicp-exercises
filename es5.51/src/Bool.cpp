#include "bool.h"

Bool::Bool(bool value)
{
    this->value = value;
}

std::string Bool::toString()
{
    return std::string(this->value ? "#t" : "#f");
}

bool Bool::is_true()
{
    return this->value;
}

bool Bool::is_false()
{
    return !this->value;
}

bool Bool::equals(const Value& other) const
{
    const Bool* other_bool = dynamic_cast<const Bool*>(&other);
    if (other_bool == NULL) {
        return false;
    }
    return this->value == other_bool->value;
}
