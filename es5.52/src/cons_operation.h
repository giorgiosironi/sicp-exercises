#ifndef CONS_OPERATION_H
#define CONS_OPERATION_H
#include "operation.h"
#include "value.h"

class ConsOperation: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
