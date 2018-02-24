#include <string>
#include "float.h"

Float::Float(float contents)
{
    this->contents = contents;
}

std::string Float::to_string() const
{
    return std::to_string(this->contents);
}

float Float::as_float()
{
    return this->contents;
}

bool Float::equals(const Value& other) const
{
    const Float* other_float = dynamic_cast<const Float*>(&other);
    if (other_float == NULL) {
        return false;
    }
    return this->contents == other_float->contents;
}
