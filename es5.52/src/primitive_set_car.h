#ifndef PRIMITIVE_SET_CAR_H
#define PRIMITIVE_SET_CAR_H
#include "primitive_procedure.h"

class PrimitiveSetCar: public PrimitiveProcedure {
    public:
        virtual Value* apply(List* arguments);
        virtual std::string to_string() const;
};

#endif
