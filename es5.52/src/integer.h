#ifndef INTEGER_H
#define INTEGER_H
#include "value.h"

class Integer : public Value
{
    private:
        int contents;
    public:
        Integer(int contents);
        virtual std::string to_string() const;
        int as_int();
        virtual bool equals(const Value& other) const;
};

#endif
