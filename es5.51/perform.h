#ifndef PERFORM_H
#define PERFORM_H
#include "operation.h"
#include "instruction.h"

class Perform: public Instruction
{
    private:
        Operation* operation;
    public:
        Perform(Operation* operation);
        virtual void execute();
};

#endif
