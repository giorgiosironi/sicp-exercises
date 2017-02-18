#include "nil.h"

std::string Nil::toString()
{
    return std::string("NIL");
}

bool Nil::equals(const Value& other) const
{
    const Nil* other_nil = dynamic_cast<const Nil*>(&other);
    if (other_nil == NULL) {
        return false;
    }
    return true;
}
