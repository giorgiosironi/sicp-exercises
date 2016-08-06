#include <string>
#include "value.h"
#include "cons.h"

Cons::Cons(Value *car_ptr, Value *cdr_ptr)
{
    this->car_ptr = car_ptr;
    this->cdr_ptr = cdr_ptr;
}

Value* Cons::car()
{
    return this->car_ptr;
}

Value* Cons::cdr()
{
    return this->cdr_ptr;
}

Value* Cons::cadadr()
{
    return ((Cons*) ((Cons*) ((Cons*) this->cdr())->car())->cdr())->car();
}

std::string Cons::toString()
{
    return std::string("(")
        + this->car_ptr->toString()
        + std::string(" . ")
        + this->cdr_ptr->toString() 
        + std::string(")");
}
