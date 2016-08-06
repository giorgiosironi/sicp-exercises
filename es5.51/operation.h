#ifndef OPERATION_H
#define OPERATION_H
#include <string>
#include <vector>
#include "value.h"

class Operation: public Value {
    public:
        virtual Value* execute(std::vector<Value*> elements) = 0;
};

class IsSelfEvaluating: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
