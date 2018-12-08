#ifndef PRIMITIVE_APPLY_H
#define PRIMITIVE_APPLY_H
#include "primitive_procedure.h"

class PrimitiveApply: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
