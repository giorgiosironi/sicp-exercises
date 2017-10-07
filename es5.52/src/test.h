#ifndef TEST_H
#define TEST_H

#include <vector>
#include "operation.h"
#include "instruction.h"
#include "machine_feedback.h"
#include "value.h"
#include "register.h"

class Test: public Instruction
{
    private:
        Register* targetRegister;
        Operation* operation;
        std::vector<Value*> operands;
    public:
        Test(Register* targetRegister, Operation* operation, std::vector<Value*> operands, MachineFeedback* machine);
        virtual void execute();
};

#endif
