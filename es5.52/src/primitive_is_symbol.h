#ifndef PRIMITIVE_IS_SYMBOL_H
#define PRIMITIVE_IS_SYMBOL_H
#include "primitive_procedure.h"

class PrimitiveIsSymbol: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
