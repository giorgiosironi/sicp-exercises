#include "nil.h"
#include "cons.h"
#define INVALID_OPERATION()  throw "Cannot access list elements of Nil"

std::string Nil::toString()
{
    return std::string("NIL");
}

bool Nil::equals(const Value& other) const
{
    const Nil* other_nil = dynamic_cast<const Nil*>(&other);
    if (other_nil == NULL) {
        return false;
    }
    return true;
}

List* Nil::append(Value* element)
{
    return Cons::fromVector({ element });
}

Value* Nil::car()
{
    INVALID_OPERATION();
}

Value* Nil::cdr()
{
    INVALID_OPERATION();
}

Value* Nil::cadr()
{
    INVALID_OPERATION();
}

Value* Nil::caadr()
{
    INVALID_OPERATION();
}

Value* Nil::cddr()
{
    INVALID_OPERATION();
}

Value* Nil::cdddr()
{
    INVALID_OPERATION();
}

Value* Nil::caddr()
{
    INVALID_OPERATION();
}

Value* Nil::cadddr()
{
    INVALID_OPERATION();
}

Value* Nil::caaddr()
{
    INVALID_OPERATION();
}

Value* Nil::cadadr()
{
    INVALID_OPERATION();
}

Value* Nil::cadaddr()
{
    INVALID_OPERATION();
}
