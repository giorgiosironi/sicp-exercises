#ifndef PERFORM_H
#define PERFORM_H
#include <vector>
#include "operation.h"
#include "instruction.h"
#include "machine_feedback.h"
#include "value.h"
using namespace std;

class Perform: public Instruction
{
    private:
        Operation* operation;
        vector<Value*> operands;
    public:
        Perform(Operation* operation, std::vector<Value*> operands, MachineFeedback *machine);
        virtual void execute();
};

#endif
