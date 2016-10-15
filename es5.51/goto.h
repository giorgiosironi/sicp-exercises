#ifndef GOTO_H
#define GOTO_H
#include "instruction.h"
#include "machine.h"

class Goto: public Instruction
{
    private: 
        Machine* machine;
    public:
        Goto();
        virtual void execute();
};

#endif
