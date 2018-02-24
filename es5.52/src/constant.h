#ifndef CONSTANT_H
#define CONSTANT_H
#include "operation.h"
#include "value.h"

class Constant: public Operation {
    private:
        Value* constant;
    public:
        Constant(Value* constant);
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};


#endif
