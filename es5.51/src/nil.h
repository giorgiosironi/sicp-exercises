#ifndef NIL_H
#define NIL_H
#include "list.h"
#include "value.h"
#define NIL (new Nil())

class Nil : public List 
{
    public:
        virtual List* append(Value *element);
        virtual std::string toString();
        virtual bool equals(const Value& other) const;
};

#endif
