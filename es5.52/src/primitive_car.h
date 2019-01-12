#ifndef PRIMITIVE_CAR_H
#define PRIMITIVE_CAR_H
#include "primitive_procedure.h"

class PrimitiveCar: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
