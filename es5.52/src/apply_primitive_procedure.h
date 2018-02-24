#ifndef APPLY_PRIMITIVE_PROCEDURE_H
#define APPLY_PRIMITIVE_PROCEDURE_H
#include "operation.h"

class ApplyPrimitiveProcedure: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
