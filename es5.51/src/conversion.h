#ifndef CONVERSION_H
#define CONVERSION_H
#include "value.h"
#include "cons.h"
#include <iostream>
#include <typeinfo>

template <typename T> T* convert_to(Value* input)
{
    T* result = dynamic_cast<T*>(input);
    if (result == NULL) {
        auto type_name = typeid(T).name();
        cout << "Value is not the correct type (" << type_name << "): " << input->toString() << endl;
        exit(1);
    }
    return result;
}

#endif

