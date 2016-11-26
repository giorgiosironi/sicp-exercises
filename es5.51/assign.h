#ifndef ASSIGN_H
#define ASSIGN_H
#include <vector>
#include "operation.h"
#include "instruction.h"
#include "machine_feedback.h"
#include "value.h"
#include "register.h"
#include "label.h"

class Assign: public Instruction
{
    private:
        // `register` is a reserved keyword
        Register* register_;
        // these three should be a union type, but that's outside the scope
        Operation* operation;
        Label* label;
        Register* source;
        // only valid if there is an operation 
        std::vector<Value*> operands;
    public:
        Assign(Register* register_, Operation* operation, std::vector<Value*> operands, MachineFeedback *machine);
        Assign(Register* register_, Label* label, MachineFeedback *machine);
        Assign(Register* register_, Register* source, MachineFeedback *machine);
        virtual void execute();
};

#endif
