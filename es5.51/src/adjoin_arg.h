#ifndef ADJOIN_ARG_H
#define ADJOIN_ARG_H
#include "operation.h"

class AdjoinArg: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string();
};

#endif
