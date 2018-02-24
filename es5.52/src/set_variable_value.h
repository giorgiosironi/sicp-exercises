#ifndef SET_VARIABLE_VALUE_H
#define SET_VARIABLE_VALUE_H
#include "operation.h"

class SetVariableValue: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
