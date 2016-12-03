#include "machine_feedback.h"
using namespace std;

void MachineFeedback::nextInstruction()
{
    this->pc++;
}

void MachineFeedback::forceInstruction(int instructionIndex)
{
    this->pc = instructionIndex;
}

Register* MachineFeedback::get_register(string name)
{
    return this->registers[name];
}
