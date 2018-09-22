#include "label_noop.h"
#include <iostream>
using namespace std;

LabelNoop::LabelNoop(std::string name, MachineFeedback* machine)
{
    this->name = name;
    this->machine_feedback = machine;
}

void LabelNoop::execute()
{
    cerr << "[e] " << "Label: " << this->name << endl;
    this->machine_feedback->next_instruction();
}
