#ifndef CONVERSION_H
#define CONVERSION_H
#include "value.h"
#include "cons.h"
#include <iostream>
#include <typeinfo>
#include <stdexcept>

template <typename T> T* convert_to(Value* input)
{
    T* result = dynamic_cast<T*>(input);
    if (result == NULL) {
        auto type_name = typeid(T).name();

        throw std::invalid_argument("Value is not the correct type (" + std::string(type_name) + "): " + input->toString());
    }
    return result;
}

template <typename T> bool is(Value* input)
{
    T* result = dynamic_cast<T*>(input);
    return result != NULL;
}


#endif

