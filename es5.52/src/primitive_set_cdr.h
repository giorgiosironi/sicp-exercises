#ifndef PRIMITIVE_SET_CDR_H
#define PRIMITIVE_SET_CDR_H
#include "primitive_procedure.h"

class PrimitiveSetCdr: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
