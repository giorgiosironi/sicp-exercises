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
        Value* car();
        Value* cdr();
        Value* caadr();
        Value* cadr();
        Value* cddr();
        Value* cdddr();
        Value* caddr();
        Value* cadddr();
        Value* caaddr();
        Value* cadadr();
        Value* cadaddr();
        virtual Cons* append(Value *element);
        virtual std::string toString();
        virtual bool equals(const Value& other) const;
        virtual std::vector<Value*> toVector();
        static List* fromVector(std::vector<Value*> vector);
};

#endif
