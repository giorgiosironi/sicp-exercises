#ifndef LINKAGE_H
#define LINKAGE_H
#include "instruction_sequence.h"

class Linkage
{
    public:
        InstructionSequence* use_to_end_with(InstructionSequence* original);
        vector<Symbol*> all_registers();
        virtual InstructionSequence* compile() = 0;
};

class LinkageNext : public Linkage
{
    public:
        virtual InstructionSequence* compile();
};

class LinkageJump : public Linkage
{
    public:
        virtual InstructionSequence* compile_proc_appl(Symbol* target);
        // seems not to be necessary to redefine it here
        //virtual InstructionSequence* compile() = 0;
};

class LinkageReturn : public LinkageJump
{
    public:
        // TODO?
        // LinkageReturn(Symbol* label);
        virtual InstructionSequence* compile();
};

class LinkageLabel : public LinkageJump
{
    private:
        Symbol* label;
    public:
        LinkageLabel(Symbol* label);
        virtual InstructionSequence* compile();
};

#endif
