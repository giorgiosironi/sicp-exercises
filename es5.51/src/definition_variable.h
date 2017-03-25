#ifndef DEFINITION_VARIABLE_H
#define DEFINITION_VARIABLE_H
#include "operation.h"
#include "symbol.h"

class DefinitionVariable: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
