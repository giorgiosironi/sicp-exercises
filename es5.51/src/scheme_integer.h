#ifndef SCHEME_INTEGER_H
#define SCHEME_INTEGER_H
#include "value.h"

class SchemeInteger : public Value
{
    private:
        int contents;
    public:
        SchemeInteger(int contents);
        virtual std::string toString();
};

#endif
