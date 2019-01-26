#ifndef PRIMITIVE_LENGTH_H
#define PRIMITIVE_LENGTH_H
#include "primitive_procedure.h"

class PrimitiveLength: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
