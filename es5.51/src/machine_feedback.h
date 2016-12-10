#ifndef MACHINE_FEEDBACK_H
#define MACHINE_FEEDBACK_H
#include <map>
#include <string>
#include "register.h"
using namespace std;

/**
 * Class extracted to avoid creating a mutual dependency between Instruction
 * and Machine
 */
class MachineFeedback {

    public:
        virtual void nextInstruction();
        virtual void forceInstruction(int instructionIndex);
        virtual Register* get_register(string name);
        void allocate_register(std::string name);
    protected:
        int pc;
        map<std::string,Register*> registers;
};

#endif
