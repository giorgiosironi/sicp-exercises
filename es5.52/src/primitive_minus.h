#ifndef PRIMITIVE_MINUS_H
#define PRIMITIVE_MINUS_H
#include "primitive_procedure.h"

class PrimitiveMinus: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
