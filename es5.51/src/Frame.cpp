#include "frame.h"
using namespace std;

Frame::Frame()
{
    this->names = vector<Symbol*>();
    this->values = vector<Value*>();
}

Frame::Frame(vector<Symbol*> names, vector<Value*> values)
{
    this->names = names;
    this->values = values;
}

Value* Frame::lookup(Symbol* symbol)
{
    for (int i = 0; i < this->names.size(); i++) {
        if (this->names.at(i)->name() == symbol->name()) {
            return this->values.at(i);
        }
    }
    return NULL;
}

void Frame::set(Symbol* symbol, Value* value)
{
    for (int i = 0; i < this->names.size(); i++) {
        if (this->names.at(i)->name() == symbol->name()) {
            this->values[i] = value;
            return;
        }
    }
    this->names.push_back(symbol);
    this->values.push_back(value);
}
