#ifndef LABEL_NOOP_H
#define LABEL_NOOP_H
#include <string>
#include "machine.h"
#include "instruction.h"
using namespace std;

class LabelNoop : public Instruction
{
    private:
        Machine* machine;
        string name;
    public:
        LabelNoop(string name, Machine* machine);
        virtual void execute();
};

#endif
