#include "perform.h"
#include <iostream>
using namespace std;

Perform::Perform(Operation* operation, std::vector<Value*> operands, MachineFeedback* machine)
{
    this->operation = operation;
    this->operands = operands;
    this->machine_feedback = machine;
}

void Perform::execute()
{
    auto elements = this->fetch_operands(this->operands);
    cerr << "Perform: " << this->operation->toString() << " [";
    for (int i = 0; i < elements.size(); i++) {
        cerr << elements[i]->toString();
        cerr << ", ";
    }
    cerr << "]" << endl;
    this->operation->execute(elements);
    this->machine_feedback->nextInstruction();
}
