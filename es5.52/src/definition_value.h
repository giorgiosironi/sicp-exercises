#ifndef DEFINITION_VALUE_H
#define DEFINITION_VALUE_H
#include "operation.h"
#include "symbol.h"

class DefinitionValue: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
