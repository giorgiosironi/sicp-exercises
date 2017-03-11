#ifndef LIST_H
#define LIST_H
#include "value.h"

class List : public Value
{
    public:
        virtual List* append(Value *element) = 0;
};

#endif
