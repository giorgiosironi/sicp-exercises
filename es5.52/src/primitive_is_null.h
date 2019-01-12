#ifndef PRIMITIVE_IS_NULL_H
#define PRIMITIVE_IS_NULL_H
#include "primitive_procedure.h"

class PrimitiveIsNull: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
