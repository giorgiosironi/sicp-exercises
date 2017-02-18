#include <string>
#include "value.h"
#include "cons.h"
#include "nil.h"
#include <iostream>
#include <typeinfo>

Cons::Cons(Value *car_ptr, Value *cdr_ptr)
{
    if (car_ptr == NULL) {
        throw "cat_ptr cannot be null";
    }
    if (cdr_ptr == NULL) {
        throw "cat_ptr cannot be null";
    }
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

Value* Cons::caadr()
{
    return ((Cons*) ((Cons*) this->cdr())->car())->car();
}

Value* Cons::cddr()
{
    return ((Cons*) this->cdr())->cdr();
}

Value* Cons::cdddr()
{
    return ((Cons*) ((Cons*) this->cdr())->cdr())->cdr();
}

Value* Cons::caddr()
{
    return ((Cons*) ((Cons*) this->cdr())->cdr())->car();
}

Value* Cons::cadddr()
{
    return ((Cons*) ((Cons*) ((Cons*) this->cdr())->cdr())->cdr())->car();
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

Cons* Cons::append(Value* element)
{
    auto contents = vector<Value*>();
    Value* current_element = this;
    while (current_element->toString() != "NIL") {
        contents.push_back(((Cons* ) current_element)->car());
        current_element = ((Cons*) current_element)->cdr();
    }
    auto list = new Cons(element, new Nil());
    for(std::vector<Value*>::reverse_iterator rit = contents.rbegin(); rit != contents.rend(); ++rit) {
        list = new Cons(*rit, list);
    }
    return list;
}

bool Cons::equals(const Value& other) const
{
    const Cons* other_cons = dynamic_cast<const Cons*>(&other);
    if (other_cons == NULL) {
        return false;
    }
    return *this->car_ptr == *other_cons->car_ptr
        && *this->cdr_ptr == *other_cons->cdr_ptr;
}

std::string Cons::toString()
{
    if (this->cdr_ptr->toString() == NIL->toString()) {
        return std::string("(")
            + this->car_ptr->toString()
            + std::string(")");
    }
    std::string rest = this->cdr_ptr->toString();
    this->car_ptr->toString();
    return std::string("(")
        + this->car_ptr->toString()
        + std::string(" ")
        + rest.substr(1, rest.size() - 1);
}

std::vector<Value*> Cons::toVector()
{
    std::vector<Value*> result = std::vector<Value*>();
    result.push_back(this->car_ptr);
    Value* rest = (Cons*) this->cdr_ptr;
    while (rest->toString() != NIL->toString()) {
        result.push_back(((Cons* ) rest)->car_ptr);
        rest = ((Cons* ) rest)->cdr_ptr;
    }
    return result;
}


Value* Cons::fromVector(std::vector<Value*> vector) {
    Value* result = new Nil();
    for(std::vector<Value*>::reverse_iterator rit = vector.rbegin(); rit != vector.rend(); ++rit) {
        result = new Cons(*rit, result);
    }
    return result;
}
