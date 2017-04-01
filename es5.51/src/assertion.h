#ifndef ASSERTION_H
#define ASSERTION_H
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T> void assert_elements(std::vector<T> v, int count)
{
    if (v.size() != count) {
        throw std::length_error("Value asserted is not " + std::to_string(count) + " elements long as requested");
    }
}

#endif
