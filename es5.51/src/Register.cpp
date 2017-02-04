#include "register.h"
#include <iostream>
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
        cout << "Attempting to get a value from Register " << this->_name << ", which has not been initialized" << endl;
        exit(1);
    }
    return this->content;
}

string Register::name()
{
    return this->_name;
}
