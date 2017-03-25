#include "nil.h"
#include "cons.h"

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
    return NULL;
}

Value* Nil::cdr()
{
    return NULL;
}

Value* Nil::cadr()
{
    return NULL;
}

Value* Nil::caadr()
{
    return NULL;
}

Value* Nil::cddr()
{
    return NULL;
}

Value* Nil::cdddr()
{
    return NULL;
}

Value* Nil::caddr()
{
    return NULL;
}

Value* Nil::cadddr()
{
    return NULL;
}

Value* Nil::caaddr()
{
    return NULL;
}

Value* Nil::cadadr()
{
    return NULL;
}

Value* Nil::cadaddr()
{
    return NULL;
}
