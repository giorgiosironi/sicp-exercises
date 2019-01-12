#ifndef PRIMITIVE_LESS_THAN_H
#define PRIMITIVE_LESS_THAN_H
#include "primitive_procedure.h"

class PrimitiveLessThan: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
