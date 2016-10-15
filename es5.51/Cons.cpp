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

Value* Cons::cadr()
{
    return ((Cons*) this->cdr())->car();
}

Value* Cons::cddr()
{
    return ((Cons*) this->cdr())->cdr();
}

Value* Cons::caddr()
{
    return ((Cons*) ((Cons*) this->cdr())->cdr())->car();
}

Value* Cons::caaddr()
{
    return ((Cons*) ((Cons*) ((Cons*) this->cdr())->cdr())->car())->car();
}

Value* Cons::cadadr()
{
    return ((Cons*) ((Cons*) ((Cons*) this->cdr())->car())->cdr())->car();
}

Value* Cons::cadaddr()
{
    return ((Cons*) ((Cons*) ((Cons*) ((Cons*) this->cdr())->cdr())->car())->cdr())->car();
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
    std::vector<Value*> result = std::vector<Value*>();
    result.push_back(this->car_ptr);
    Cons* rest = (Cons*) this->cdr_ptr;
    while (rest->toString() != NIL->toString()) {
        result.push_back(rest->car_ptr);
    }
    return result;
}
