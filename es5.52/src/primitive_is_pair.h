#ifndef PRIMITIVE_IS_PAIR_H
#define PRIMITIVE_IS_PAIR_H
#include "primitive_procedure.h"

class PrimitiveIsPair: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
