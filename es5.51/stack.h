#ifndef STACK_H
#define STACK_H
#include <stack>
#include "value.h"

class Stack {
    public:
        void initialize();
        void push(Value* element);
        Value* pop();

    private:
        std::stack<Value*> *contents;
            
};

#endif
