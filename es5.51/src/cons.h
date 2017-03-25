#ifndef CONS_H
#define CONS_H
#include "list.h"
#include <string>
#include <vector>

class Cons : public List
{
    private:
        Value *car_ptr;
        Value *cdr_ptr;

    public:
        Cons(Value *car_ptr, Value *cdr_ptr);
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
        virtual Cons* append(Value *element);
        virtual std::string toString();
        virtual bool equals(const Value& other) const;
        virtual std::vector<Value*> toVector();
        static List* fromVector(std::vector<Value*> vector);
};

#endif
