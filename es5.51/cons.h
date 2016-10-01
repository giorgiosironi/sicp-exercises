#ifndef CONS_H
#define CONS_H

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
};

#endif
