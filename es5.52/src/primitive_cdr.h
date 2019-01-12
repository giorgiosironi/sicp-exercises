#ifndef PRIMITIVE_CDR_H
#define PRIMITIVE_CDR_H
#include "primitive_procedure.h"

class PrimitiveCdr: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
