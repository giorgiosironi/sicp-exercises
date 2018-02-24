#include "value.h"
#include <string>
#include <typeinfo>
#include <iostream>

// http://stackoverflow.com/questions/13045399/how-to-implement-operator-for-polymorphic-classes-in-c
bool operator==(const Value& lhs, const Value& rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equals(rhs);
}

bool operator!=(const Value& lhs, const Value& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Value& lhs, const Value& rhs)
{
    // approximate, but we only need this for set ordering
    if (typeid(lhs) != typeid(rhs)) {
        return false;
    }

    return lhs.to_string() < rhs.to_string();
}

bool Value::equals(const Value& other) const
{
    return false;
}
