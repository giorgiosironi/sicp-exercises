#ifndef ASSIGN_H
#define ASSIGN_H
#include <vector>
#include "operation.h"
#include "instruction.h"
#include "machine.h"
#include "value.h"
#include "register.h"
#include "label.h"

class Assign: public Instruction
{
    private:
        // `register` is a reserved keyword
        Register* register_;
        // these two should be a union type, but that's outside the scope
        Operation* operation;
        Label* label;
        // only valid if there is an operation 
        std::vector<Value*> operands;
        Machine* machine;
    public:
        Assign(Register* register_, Operation* operation, std::vector<Value*> operands, Machine *machine);
        Assign(Register* register_, Label* label, Machine *machine);
        virtual void execute();
};

#endif
