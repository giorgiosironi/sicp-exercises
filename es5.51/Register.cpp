#include "register.h"
using namespace std;

Register::Register(string name)
{
    this->_name = name;
}

void Register::set(Value* value)
{
    this->content = value;
}

Value* Register::get()
{
    return this->content;
}

string Register::name()
{
    return this->_name;
}
