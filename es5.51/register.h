#ifndef REGISTER_H
#define REGISTER_H
#include "value.h"

class Register {
    public:
        void set(Value* element);
        Value* get();

    private:
        Value* content;
};

#endif
