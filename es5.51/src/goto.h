#ifndef GOTO_H
#define GOTO_H
#include "instruction.h"
#include "machine_feedback.h"

class Goto: public Instruction
{
    private: 
        int labelIndex;
    public:
        Goto(MachineFeedback* machine, int labelIndex);
        virtual void execute();
};

#endif
