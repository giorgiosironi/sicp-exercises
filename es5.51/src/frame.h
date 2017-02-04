#ifndef FRAME_H
#define FRAME_H
#include <vector>
#include "value.h"
#include "symbol.h"
using namespace std;

class Frame {
    private:
        vector<Symbol*> names;
        vector<Value*> values;
    public:
        Frame(vector<Symbol*> names, vector<Value*> values);
        Value* lookup(Symbol* symbol);
        void set(Symbol* symbol, Value* value);
};

#endif
