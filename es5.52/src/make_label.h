#ifndef MAKE_LABEL_H
#define MAKE_LABEL_H
#include "symbol.h"
#include "string.h"
using namespace std;

class MakeLabel {
    private:
        int counter = 0;
    public:
        Symbol* next(string prefix);
        void reset();
};

#endif
