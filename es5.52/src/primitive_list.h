#ifndef PRIMITIVE_LIST_H
#define PRIMITIVE_LIST_H
#include "primitive_procedure.h"

class PrimitiveList: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
