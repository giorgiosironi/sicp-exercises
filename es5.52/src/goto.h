#ifndef GOTO_H
#define GOTO_H
#include "instruction.h"
#include "machine_feedback.h"

class Goto: public Instruction
{
    private: 
        int labelIndex;
        Register* index;
    public:
        Goto(MachineFeedback* machine, int labelIndex);
        Goto(MachineFeedback* machine, Register* index);
        virtual void execute();
};

#endif
