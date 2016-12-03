#include "label.h"
using namespace std;

Label::Label(Symbol* name)
{
    this->_name = name;
}

Symbol* Label::name()
{
    return this->_name;
}

string Label::toString()
{
    return "(label:" + this->_name->name() + ")";
}
