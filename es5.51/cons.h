#ifndef CONS_H
#define CONS_H
#include "value.h"
#include <string>
#include <vector>

class Cons : public Value
{
    private:
        Value *car_ptr;
        Value *cdr_ptr;

    public:
        Cons(Value *car_ptr, Value *cdr_ptr);
        Value* car();
        Value* cdr();
        Value* cddr();
        Value* cadadr();
        virtual std::string toString();
        virtual std::vector<Value*> toVector();
};

#endif
