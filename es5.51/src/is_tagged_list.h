#ifndef IS_TAGGED_LIST_H
#define IS_TAGGED_LIST_H
#include "operation.h"
#include "symbol.h"

class IsTaggedList: public Operation {
    private:
        Symbol* tag;
    public:
        IsTaggedList(Symbol* tag);
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
};

#endif
