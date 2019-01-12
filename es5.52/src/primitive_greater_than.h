#ifndef PRIMITIVE_GREATER_THAN_H
#define PRIMITIVE_GREATER_THAN_H
#include "primitive_procedure.h"

class PrimitiveGreaterThan: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
