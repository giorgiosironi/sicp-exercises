#include "value.h"
#include <string>
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

class Example
{
    public:
        std::string to_string() const
        {
            return "";
        }
};

bool operator<(const Value& lhs, const Value& rhs)
{
    // approximate, but we only need this for set ordering
    if (typeid(lhs) != typeid(rhs)) {
        return false;
    }

    //const Example example = Example();
    //return example.to_string() == "";

    return lhs.to_string() < rhs.to_string();
}

bool Value::equals(const Value& other) const
{
    return false;
}
