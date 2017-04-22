#ifndef PRIMITIVE_TIMES_H
#define PRIMITIVE_TIMES_H
#include "primitive_procedure.h"

class PrimitiveTimes: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string();
};

#endif
