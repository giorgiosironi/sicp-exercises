#ifndef TEST_H
#define TEST_H

#include <vector>
#include "operation.h"
#include "instruction.h"
#include "machine.h"
#include "value.h"
#include "register.h"
#include "label.h"

class Test: public Instruction
{
    private:
        Register* targetRegister;
        Machine *machine;
    public:
        Test(Register* targetRegister, Machine* machine);
        virtual void execute();
};

#endif
