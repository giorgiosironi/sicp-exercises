#ifndef ASSERTION_H
#define ASSERTION_H
#include <stdexcept>
#include <vector>
#include <stack>
#include <typeinfo>

/**
 * http://man7.org/linux/man-pages/man3/backtrace.3.html
 */
void dump_stacktrace();

template <typename T> void assert_elements(std::vector<T> v, int count)
{
    if (v.size() != count) {
        dump_stacktrace();

        auto type_name = typeid(T).name();
        throw std::length_error("Value vector<" + std::string(type_name) + "> asserted is not " + std::to_string(count) + " elements long as requested, but " + std::to_string(v.size()));
    }
}

template <typename T> void assert_not_empty(std::stack<T> v)
{
    if (v.size() == 0) {
        throw std::length_error("Stack is empty");
    }
}

#endif
