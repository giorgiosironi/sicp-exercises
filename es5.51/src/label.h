#ifndef LABEL_H
#define LABEL_H
#include <string>
#include "value.h"
#include "symbol.h"
using namespace std;

class Label: public Value {
    public:
        Label(Symbol* name);
        Symbol* name();
        virtual string toString();
    private:
        Symbol* _name;
};

#endif
