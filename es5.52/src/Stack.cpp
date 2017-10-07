#include "stack.h"
#include "assertion.h"
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
    assert_not_empty(*this->contents);
    Value* element = this->contents->top();
    this->contents->pop();
    return element;
}
