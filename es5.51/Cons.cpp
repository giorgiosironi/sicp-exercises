#include <string>
#include "value.h"
#include "cons.h"
#include "nil.h"

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

Value* Cons::cddr()
{
    return ((Cons*) this->cdr())->cdr();
}

Value* Cons::cadadr()
{
    return ((Cons*) ((Cons*) ((Cons*) this->cdr())->car())->cdr())->car();
}

std::string Cons::toString()
{
    if (this->cdr_ptr->toString() == NIL->toString()) {
        return std::string("(")
            + this->car_ptr->toString()
            + std::string(")");
    }
    std::string rest = this->cdr_ptr->toString();
    return std::string("(")
        + this->car_ptr->toString()
        + std::string(" ")
        + rest.substr(1, rest.size() - 1);
}

std::vector<Value*> Cons::toVector()
{
    return std::vector<Value*>();
}
