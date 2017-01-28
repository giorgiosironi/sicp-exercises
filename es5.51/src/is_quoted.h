#ifndef IS_QUOTED_H
#define IS_QUOTED_H
#include "operation.h"

class IsQuoted: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
