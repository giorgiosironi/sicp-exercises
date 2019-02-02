#ifndef PRIMITIVE_EQ_H
#define PRIMITIVE_EQ_H
#include "primitive_procedure.h"

class PrimitiveEq: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
