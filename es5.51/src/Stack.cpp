#include "stack.h"
#include <iostream>

Stack::Stack()
{
    this->contents = new std::stack<Value*>();
}

/**
 * Resets the stack to be empty.
 */
void Stack::initialize()
{
    this->contents = new std::stack<Value*>();
}

void Stack::push(Value* element)
{
    return this->contents->push(element);
}

int Stack::size()
{
    return this->contents->size();
}

Value* Stack::pop()
{
    if (this->contents->size() == 0) {
        cout << "Cannot pop from an empty stack" << endl;
        exit(1);
    }
    Value* element = this->contents->top();
    this->contents->pop();
    return element;
}
