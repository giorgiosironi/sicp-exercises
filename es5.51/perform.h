#ifndef PERFORM_H
#define PERFORM_H
#include <vector>
#include "operation.h"
#include "instruction.h"
#include "machine.h"
#include "value.h"

class Perform: public Instruction
{
    private:
        Operation* operation;
        std::vector<Value*> operands;
        Machine* machine;
    public:
        Perform(Operation* operation, std::vector<Value*> operands, Machine *machine);
        virtual void execute();
};

#endif