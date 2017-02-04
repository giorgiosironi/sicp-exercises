
#ifndef RESTORE_H
#define RESTORE_H
#include <vector>
#include "operation.h"
#include "instruction.h"
#include "stack.h"
#include "register.h"
#include "machine_feedback.h"
#include "value.h"

class Restore: public Instruction
{
    private:
        Stack* stack;
        Register* register_;
        MachineFeedback* machine_feedback;
    public:
        Restore(Stack* stack, Register* register_, MachineFeedback* machine);
        virtual void execute();
};

#endif
