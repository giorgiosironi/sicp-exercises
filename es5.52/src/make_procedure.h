#ifndef MAKE_PROCEDURE_H
#define MAKE_PROCEDURE_H
#include "operation.h"

class MakeProcedure: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
