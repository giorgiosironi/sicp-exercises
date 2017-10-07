#include "register.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Register::Register(string name)
{
    this->_name = name;
    this->content = NULL;
}

void Register::set(Value* value)
{
    this->content = value;
}

Value* Register::get()
{
    if (this->content == NULL) {
        throw runtime_error("Attempting to get a value from Register " + this->_name + ", which has not been initialized");
    }
    return this->content;
}

string Register::name()
{
    return this->_name;
}
