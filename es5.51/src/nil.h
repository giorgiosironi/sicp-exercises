#ifndef NIL_H
#define NIL_H
#include "list.h"
#include "value.h"
#define NIL (new Nil())

class Nil : public List 
{
    public:
        virtual List* append(Value *element);
        virtual Value* car();
        virtual Value* cdr();
        virtual Value* caadr();
        virtual Value* cadr();
        virtual Value* cddr();
        virtual Value* cdadr();
        virtual Value* cdddr();
        virtual Value* caddr();
        virtual Value* cadddr();
        virtual Value* caaddr();
        virtual Value* cadadr();
        virtual Value* cadaddr();
        virtual std::string toString();
        virtual bool equals(const Value& other) const;
};

#endif
