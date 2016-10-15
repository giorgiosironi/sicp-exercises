#include "label_noop.h"
#include <iostream>
using namespace std;

LabelNoop::LabelNoop(std::string name, Machine* machine)
{
    this->name = name;
    this->machine = machine;
}

void LabelNoop::execute()
{
    cout << "Label: " << this->name << endl;
    this->machine->nextInstruction();
}
