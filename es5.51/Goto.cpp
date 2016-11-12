#include "goto.h"
#include <iostream>
using namespace std;

Goto::Goto(Machine* machine, int labelIndex)
{
    this->machine = machine;
    this->labelIndex = labelIndex;
}

void Goto::execute()
{
    cout << "Goto(" << this->labelIndex << ")" << endl;
    this->machine->forceInstruction(this->labelIndex);
}
