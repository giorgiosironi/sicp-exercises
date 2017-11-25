#ifndef LINKAGE_H
#define LINKAGE_H
#include "instruction_sequence.h"

class Linkage
{
    public:
        virtual InstructionSequence* compile() = 0;
};

class LinkageNext : public Linkage
{
    public:
        virtual InstructionSequence* compile();
};

#endif
