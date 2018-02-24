#ifndef IS_SELF_EVALUATING_H
#define IS_SELF_EVALUATING_H
#include "operation.h"

class IsSelfEvaluating: public Operation {
    public:
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string to_string() const;
};

#endif
