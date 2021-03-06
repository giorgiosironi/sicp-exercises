#ifndef LINKAGE_H
#define LINKAGE_H
#include "instruction_sequence.h"

class Linkage
{
    public:
        InstructionSequence* use_to_end_with(InstructionSequence* original);
        vector<Symbol*> all_registers();
        virtual InstructionSequence* compile() = 0;
        virtual Linkage* lambda_linkage(Symbol* after_lambda) = 0;
};

class LinkageNext : public Linkage
{
    public:
        virtual InstructionSequence* compile();
        virtual Linkage* lambda_linkage(Symbol* after_lambda);
};

class LinkageJump : public Linkage
{
    protected:
        Symbol* _label;
    public:
        virtual InstructionSequence* compile_proc_appl(Symbol* target) = 0;
        // seems not to be necessary to redefine it here
        //virtual InstructionSequence* compile() = 0;
        virtual Linkage* lambda_linkage(Symbol* after_lambda);
};

class LinkageReturn : public LinkageJump
{
    public:
        virtual InstructionSequence* compile();
        virtual InstructionSequence* compile_proc_appl(Symbol* target);
};

class LinkageLabel : public LinkageJump
{
    public:
        LinkageLabel(Symbol* label);
        virtual InstructionSequence* compile();
        virtual InstructionSequence* compile_proc_appl(Symbol* target);
};

#endif
