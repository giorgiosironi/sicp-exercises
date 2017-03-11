#ifndef PRIMITIVE_PROCEDURE_H
#define PRIMITIVE_PROCEDURE_H
#include <string>
#include "value.h"
#include "list.h"

class PrimitiveProcedure: public Value {
    public:
        virtual Value* apply(List* arguments) = 0;
        virtual std::string toString() = 0;
};

#endif
