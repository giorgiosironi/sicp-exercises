#ifndef PRIMITIVE_APPLY_IN_UNDERLYING_SCHEME_H
#define PRIMITIVE_APPLY_IN_UNDERLYING_SCHEME_H
#include "primitive_procedure.h"

class PrimitiveApplyInUnderlyingScheme: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
