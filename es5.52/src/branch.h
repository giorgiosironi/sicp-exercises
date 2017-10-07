#ifndef BRANCH_H
#define BRANCH_H
#include "instruction.h"
#include "register.h"
#include "machine_feedback.h"

class Branch: public Instruction
{
    private: 
        Register *test;
        int labelIndex;
    public:
        Branch(Register* test, MachineFeedback* machine, int labelIndex);
        virtual void execute();
};


#endif
