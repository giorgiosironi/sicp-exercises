#ifndef DEFINE_VARIABLE_H
#define DEFINE_VARIABLE_H
#include "operation.h"

class DefineVariable: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
