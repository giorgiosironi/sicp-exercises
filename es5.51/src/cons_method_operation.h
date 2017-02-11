#ifndef IS_CONS_METHOD_OPERATION_H
#define IS_CONS_METHOD_OPERATION_H
#include "operation.h"
#include "cons.h"

class ConsMethodOperation: public Operation {
    private:
        Value* (Cons::*method_to_call)();
    public:
        ConsMethodOperation(Value* (Cons::*method_to_call)());
        virtual Value* execute(std::vector<Value*> elements);
        virtual std::string toString();
        static ConsMethodOperation* car();
        static ConsMethodOperation* cdr();
        static ConsMethodOperation* cadr();
        static ConsMethodOperation* cddr();
        static ConsMethodOperation* caddr();
        static ConsMethodOperation* cadddr();
};

#endif
