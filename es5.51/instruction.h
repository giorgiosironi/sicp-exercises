#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <vector>
#include "value.h"
#include "machine_feedback.h"
using namespace std;

class Instruction
{
    public:
        virtual void execute() = 0;
    protected:
        vector<Value*> fetch_operands(vector<Value*> operands);
};

#endif
