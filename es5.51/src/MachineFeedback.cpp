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

void MachineFeedback::allocate_register(std::string name)
{
    this->registers.insert(std::make_pair(
        name,
        new Register(name)
    ));
}

