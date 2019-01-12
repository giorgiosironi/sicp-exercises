#ifndef PRIMITIVE_CONS_H
#define PRIMITIVE_CONS_H
#include "primitive_procedure.h"

class PrimitiveCons: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
