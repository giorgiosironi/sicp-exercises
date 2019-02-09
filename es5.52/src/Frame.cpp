#include "frame.h"
#include "assertion.h"
using namespace std;

Frame::Frame()
{
    this->_names = vector<Symbol*>();
    this->_values = vector<Value*>();
}

Frame::Frame(vector<Symbol*> names, vector<Value*> values)
{
    assert_elements(values, names.size(), "Frame has different number of names and values");
    this->_names = names;
    this->_values = values;
}

Value* Frame::lookup(Symbol* symbol)
{
    for (int i = 0; i < this->_names.size(); i++) {
        if (this->_names.at(i)->name() == symbol->name()) {
            return this->_values.at(i);
        }
    }
    return NULL;
}

void Frame::set(Symbol* symbol, Value* value)
{
    for (int i = 0; i < this->_names.size(); i++) {
        if (this->_names.at(i)->name() == symbol->name()) {
            this->_values[i] = value;
            return;
        }
    }
    this->_names.push_back(symbol);
    this->_values.push_back(value);
}

string Frame::to_string()
{
    string representation = "Frame(";
    for (vector<Symbol*>::iterator it = this->_names.begin(); it != this->_names.end(); ++it) {
        representation = representation + (*it)->to_string() + " ";
    }
    representation = representation + ")";
    return representation;
}
