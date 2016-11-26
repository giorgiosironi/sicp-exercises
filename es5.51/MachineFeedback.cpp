#include "machine_feedback.h"

void MachineFeedback::nextInstruction()
{
    this->pc++;
}

void MachineFeedback::forceInstruction(int instructionIndex)
{
    this->pc = instructionIndex;
}

