#ifndef GOTO_H
#define GOTO_H
#include "instruction.h"
#include "machine.h"

class Goto: public Instruction
{
    private: 
        Machine* machine;
        int labelIndex;
    public:
        Goto(Machine* machine, int labelIndex);
        virtual void execute();
};

#endif
