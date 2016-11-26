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
        void nextInstruction();
        void forceInstruction(int instructionIndex);
        Register* get_register(string name);
    protected:
        int pc;
        map<std::string,Register*> registers;
};

#endif
