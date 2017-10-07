#include "value.h"
#include <typeinfo>

// http://stackoverflow.com/questions/13045399/how-to-implement-operator-for-polymorphic-classes-in-c
bool operator==(const Value& lhs, const Value& rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equals(rhs);
}

bool operator!=(const Value& lhs, const Value& rhs)
{
    return !(lhs == rhs);
}

bool Value::equals(const Value& other) const
{
    return false;
}
