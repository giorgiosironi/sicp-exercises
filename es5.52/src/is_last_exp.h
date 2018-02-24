#ifndef IS_LAST_EXP_H
#define IS_LAST_EXP_H
#include "operation.h"

class IsLastExp: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
