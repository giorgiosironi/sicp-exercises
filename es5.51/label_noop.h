#ifndef LABEL_NOOP_H
#define LABEL_NOOP_H
#include <string>
#include "instruction.h"

class LabelNoop : public Instruction
{
    private:
        std::string name;
    public:
        LabelNoop(std::string name);
        virtual void execute();
};

#endif
