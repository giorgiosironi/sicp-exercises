#ifndef IS_LAST_OPERAND_H
#define IS_LAST_OPERAND_H
#include "operation.h"
#include "bool.h"

class IsLastOperand: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
