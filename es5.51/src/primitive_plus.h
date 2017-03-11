#ifndef PRIMITIVE_PLUS_H
#define PRIMITIVE_PLUS_H
#include "primitive_procedure.h"

class PrimitivePlus: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string toString();
};

#endif
