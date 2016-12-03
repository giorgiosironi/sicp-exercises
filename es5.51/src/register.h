#ifndef REGISTER_H
#define REGISTER_H
#include <string>
#include "value.h"
using namespace std;

class Register {
    public:
        Register(string name);
        void set(Value* element);
        Value* get();
        string name();

    private:
        string _name;
        Value* content;
};

#endif
