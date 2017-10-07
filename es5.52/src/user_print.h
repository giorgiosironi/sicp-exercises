#ifndef USER_PRINT_H
#define USER_PRINT_H
#include "operation.h"

class UserPrint: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string();
};

#endif
