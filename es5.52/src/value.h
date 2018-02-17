#ifndef VALUE_H
#define VALUE_H
#include <string>
using namespace std;

class Value
{
    public:
        virtual string to_string() = 0;
        virtual bool equals(const Value& other) const;
};

bool operator==(const Value& lhs, const Value& rhs);
bool operator!=(const Value& lhs, const Value& rhs);
bool operator<(const Value& lhs, const Value& rhs);


#endif
