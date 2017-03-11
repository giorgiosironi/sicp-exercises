#ifndef CONVERSION_H
#define CONVERSION_H
#include "value.h"
#include "cons.h"
#include <iostream>

Cons* convert_to(Value* input)
{
    Cons* result = dynamic_cast<Cons*>(input);
    if (result == NULL) {
        cout << "Value is not a Cons: " << input->toString() << endl;
        exit(1);
    }
    return result;
}

#endif

