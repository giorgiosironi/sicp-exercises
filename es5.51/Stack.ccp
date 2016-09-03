#include "stack.h"

void Stack::initialize()
{
    this->contents = new std::stack<Value*>();
}

void Stack::push(Value* element)
{
    return this->contents->push(element);
}

Value* Stack::pop()
{
    Value* element = this->contents->top();
    this->contents->pop();
    return element;
}
