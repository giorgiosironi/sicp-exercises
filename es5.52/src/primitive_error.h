#ifndef PRIMITIVE_ERROR_H
#define PRIMITIVE_ERROR_H
#include "primitive_procedure.h"

class PrimitiveError: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
