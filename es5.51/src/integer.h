#ifndef SCHEME_INTEGER_H
#define SCHEME_INTEGER_H
#include "value.h"

class Integer : public Value
{
    private:
        int contents;
    public:
        Integer(int contents);
        virtual std::string toString();
        int asInt();
};

#endif
