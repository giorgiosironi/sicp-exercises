#ifndef GET_GLOBAL_ENVIRONMENT_H
#define GET_GLOBAL_ENVIRONMENT_H
#include <string>
#include <vector>
#include "value.h"
#include "operation.h"
#include "environment.h"

class GetGlobalEnvironment: public Operation {
    private:
        Environment* global_environment;
    public:
        GetGlobalEnvironment(Environment* environment);
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
