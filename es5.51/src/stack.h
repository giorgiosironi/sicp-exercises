#ifndef STACK_H
#define STACK_H
#include <stack>
#include "value.h"

class Stack {
    public:
        Stack();
        void initialize();
        void push(Value* element);
        Value* pop();
        int size();

    private:
        std::stack<Value*> *contents;
            
};

#endif
