#ifndef LINKAGE_H
#define LINKAGE_H
#include "instruction_sequence.h"

class Linkage
{
    public:
        InstructionSequence* use_to_end_with(InstructionSequence* original);
        vector<Symbol*> all_registers();
        virtual InstructionSequence* compile_proc_appl(Symbol* target);
        virtual InstructionSequence* compile() = 0;
};

class LinkageNext : public Linkage
{
    public:
        virtual InstructionSequence* compile();
};

class LinkageReturn : public Linkage
{
    public:
        virtual InstructionSequence* compile();
};

#endif
