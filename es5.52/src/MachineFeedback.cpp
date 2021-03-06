#include "machine_feedback.h"
using namespace std;

void MachineFeedback::next_instruction()
{
    this->pc++;
}

void MachineFeedback::force_instruction(int instructionIndex)
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

int MachineFeedback::get_label_index(Symbol* name)
{
    int l = this->labels[*name];
    //if (l) { // what should this condition be?
    //    throw std::logic_error("Unknown label: " + name->to_string());
    //}
    return l;
}

