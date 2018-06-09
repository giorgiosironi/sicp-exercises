#ifndef LIST_OPERATION_H
#define LIST_OPERATION_H
#include "operation.h"
#include "value.h"

class ListOperation: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
