#ifndef PRIMITIVE_IS_STRING_H
#define PRIMITIVE_IS_STRING_H
#include "primitive_procedure.h"

class PrimitiveIsString: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
