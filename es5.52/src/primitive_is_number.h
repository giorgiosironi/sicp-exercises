#ifndef PRIMITIVE_IS_NUMBER_H
#define PRIMITIVE_IS_NUMBER_H
#include "primitive_procedure.h"

class PrimitiveIsNumber: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
