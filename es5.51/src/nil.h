#ifndef NIL_H
#define NIL_H
#include <string>
#include "value.h"
#define NIL (new Nil())

class Nil : public Value 
{
    public:
        virtual std::string toString();
        virtual bool equals(const Value& other) const;
};

#endif
