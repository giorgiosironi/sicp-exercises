#ifndef LOOKUP_VARIABLE_VALUE_H
#define LOOKUP_VARIABLE_VALUE_H
#include "operation.h"

class LookupVariableValue: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string();
};

#endif
