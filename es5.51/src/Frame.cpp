#include "frame.h"

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
