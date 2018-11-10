#ifndef MACHINE_FEEDBACK_H
#define MACHINE_FEEDBACK_H
#include <map>
#include <string>
#include "register.h"
#include "symbol.h"
using namespace std;

/**
 * Class extracted to avoid creating a mutual dependency between Instruction
 * and Machine
 */
class MachineFeedback {

    public:
        virtual void next_instruction();
        virtual void force_instruction(int instructionIndex);
        virtual Register* get_register(string name);
        virtual int get_label_index(Symbol* name);
        void allocate_register(std::string name);
    protected:
        int pc;
        map<std::string,Register*> registers;
        map<Symbol,int> labels;
};

#endif
