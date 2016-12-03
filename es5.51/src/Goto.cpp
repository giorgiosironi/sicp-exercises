#include "goto.h"
#include <iostream>
using namespace std;

Goto::Goto(MachineFeedback* machine, int labelIndex)
{
    this->machine_feedback = machine;
    this->labelIndex = labelIndex;
}

void Goto::execute()
{
    cout << "Goto(" << this->labelIndex << ")" << endl;
    this->machine_feedback->forceInstruction(this->labelIndex);
}
