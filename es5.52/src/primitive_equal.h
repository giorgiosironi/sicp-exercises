#ifndef PRIMITIVE_EQUAL_H
#define PRIMITIVE_EQUAL_H
#include "primitive_procedure.h"

class PrimitiveEqual: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
