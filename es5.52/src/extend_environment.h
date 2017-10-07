#ifndef EXTEND_ENVIRONMENT_H
#define EXTEND_ENVIRONMENT_H
#include "operation.h"

class ExtendEnvironment: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string();
};

#endif
