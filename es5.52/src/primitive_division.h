#ifndef PRIMITIVE_DIVISION_H
#define PRIMITIVE_DIVISION_H
#include "primitive_procedure.h"

class PrimitiveDivision: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
