#ifndef ASSERTION_H
#define ASSERTION_H
#include <stdexcept>
#include <vector>
#include <stack>
#include <iostream>

template <typename T> void assert_elements(std::vector<T> v, int count)
{
    if (v.size() != count) {
        throw std::length_error("Value asserted is not " + std::to_string(count) + " elements long as requested");
    }
}

template <typename T> void assert_not_empty(std::stack<T> v)
{
    if (v.size() == 0) {
        throw std::length_error("Stack is empty");
    }
}

#endif
