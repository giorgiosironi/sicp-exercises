#ifndef INITIALIZE_STACK_H
#define INITIALIZE_STACK_H
#include <string>
#include <vector>
#include "value.h"
#include "operation.h"
#include "stack.h"

class InitializeStack: public Operation {
    private:
        Stack* stack;
    public:
        InitializeStack(Stack* stack);
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
