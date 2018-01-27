#ifndef LIST_H
#define LIST_H
#include <vector>
#include "value.h"

class List : public Value
{
    public:
        virtual Value* car() = 0;
        virtual Value* cdr() = 0;
        virtual Value* caadr() = 0;
        virtual Value* cadr() = 0;
        virtual Value* cddr() = 0;
        virtual Value* cdadr() = 0;
        virtual Value* cdddr() = 0;
        virtual Value* caddr() = 0;
        virtual Value* cadddr() = 0;
        virtual Value* caaddr() = 0;
        virtual Value* cadadr() = 0;
        virtual Value* cadaddr() = 0;
        virtual List* append(Value *element) = 0;
        virtual List* append_list(List *next) = 0;
        virtual std::vector<Value*> to_vector() = 0;
};

#endif
