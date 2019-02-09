#ifndef FRAME_H
#define FRAME_H
#include <vector>
#include "value.h"
#include "symbol.h"
using namespace std;

class Frame {
    private:
        vector<Symbol*> _names;
        vector<Value*> _values;
    public:
        Frame();
        Frame(vector<Symbol*> names, vector<Value*> values);
        Value* lookup(Symbol* symbol);
        void set(Symbol* symbol, Value* value);
        string to_string();
};

#endif
