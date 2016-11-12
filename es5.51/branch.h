#ifndef BRANCH_H
#define BRANCH_H
#include "instruction.h"
#include "register.h"
#include "machine.h"

class Branch: public Instruction
{
    private: 
        Register *test;
        Machine* machine;
        int labelIndex;
    public:
        Branch(Register* test, Machine* machine, int labelIndex);
        virtual void execute();
};


#endif
