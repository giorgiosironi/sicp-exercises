#ifndef MAKE_COMPILED_PROCEDURE_H
#define MAKE_COMPILED_PROCEDURE_H
#include "operation.h"

class MakeCompiledProcedure: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
