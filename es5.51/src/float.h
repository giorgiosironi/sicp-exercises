#ifndef FLOAT_H
#define FLOAT_H
#include "value.h"

class Float : public Value
{
    private:
        float contents;
    public:
        Float(float contents);
        virtual std::string to_string();
        float as_float();
        virtual bool equals(const Value& other) const;
};

#endif
