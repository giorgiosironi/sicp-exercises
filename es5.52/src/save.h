#ifndef SAVE_H
#define SAVE_H
#include <vector>
#include "operation.h"
#include "instruction.h"
#include "stack.h"
#include "register.h"
#include "machine_feedback.h"
#include "value.h"

class Save: public Instruction
{
    private:
        Stack* stack;
        Register* register_;
        MachineFeedback* machine_feedback;
    public:
        Save(Stack* stack, Register* register_, MachineFeedback* machine);
        virtual void execute();
};

#endif
