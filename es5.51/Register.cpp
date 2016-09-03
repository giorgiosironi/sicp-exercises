#include "register.h"

void Register::set(Value* value)
{
    this->content = value;
}

Value* Register::get()
{
    return this->content;
}
