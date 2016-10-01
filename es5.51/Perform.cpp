#include "perform.h"
#include <iostream>
using namespace std;

Perform::Perform(Operation* operation, std::vector<Value*> operands, Machine* machine)
{
    this->operation = operation;
    this->operands = operands;
    this->machine = machine;
}

void Perform::execute()
{
    cout << "Perform: " << this->operation->toString() << endl;
    cout << "operands length: " << this->operands.size() << endl;
    for (std::vector<Value*>::iterator it = this->operands.begin() ; it != this->operands.end(); ++it) {
        cout << "operand: " << (*it)->toString() << endl;
    }
    // only 0 arguments calls are supported yet
    auto elements = std::vector<Value*>();
    this->operation->execute(elements);
}
