#include "goto.h"
#include <iostream>
using namespace std;

Goto::Goto(Machine* machine)
{
    this->machine = machine;
}

void Goto::execute()
{
    cout << "GOTO" << endl;
    // TODO: shouldn't do this, but go to a label
    this->machine->nextInstruction();
}
