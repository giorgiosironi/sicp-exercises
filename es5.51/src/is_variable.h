#ifndef IS_VARIABLE_H
#define IS_VARIABLE_H
#include "operation.h"

class IsVariable: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
