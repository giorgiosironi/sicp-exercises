#ifndef PRIMITIVE_NEWLINE_H
#define PRIMITIVE_NEWLINE_H
#include "primitive_procedure.h"

class PrimitiveNewline: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
