#ifndef PRIMITIVE_DISPLAY_H
#define PRIMITIVE_DISPLAY_H
#include "primitive_procedure.h"

class PrimitiveDisplay: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
