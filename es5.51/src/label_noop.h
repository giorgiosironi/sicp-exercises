#ifndef LABEL_NOOP_H
#define LABEL_NOOP_H
#include <string>
#include "machine_feedback.h"
#include "instruction.h"
using namespace std;

class LabelNoop : public Instruction
{
    private:
        string name;
    public:
        LabelNoop(string name, MachineFeedback* machine);
        virtual void execute();
};

#endif
