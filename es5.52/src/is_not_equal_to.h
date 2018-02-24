#ifndef IS_NOT_EQUAL_TO_H
#define IS_NOT_EQUAL_TO_H
#include "operation.h"

class IsNotEqualTo: public Operation {
    private:
        Value* reference;
    public:
        IsNotEqualTo(Value* reference);
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
