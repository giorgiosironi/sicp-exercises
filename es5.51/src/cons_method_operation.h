#ifndef IS_CONS_METHOD_OPERATION_H
#define IS_CONS_METHOD_OPERATION_H
#include "operation.h"
#include "cons.h"

class ConsMethodOperation: public Operation {
    public:
        ConsMethodOperation();
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
