#ifndef IS_EQUAL_TO_H
#define IS_EQUAL_TO_H
#include "operation.h"

class IsEqualTo: public Operation {
    private:
        Value* reference;
    public:
        IsEqualTo(Value* reference);
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
