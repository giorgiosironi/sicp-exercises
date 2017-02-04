#include "restore.h"
#include <iostream>
using namespace std;

Restore::Restore(Stack* stack, Register* register_, MachineFeedback* machine)
{
    this->stack = stack;
    this->register_ = register_;
    this->machine_feedback = machine;
}

void Restore::execute()
{
    auto value = this->stack->pop();
    cout << "Restore (" << this->register_->name() << "): " << value->toString() << endl;
    this->register_->set(value);
    this->machine_feedback->nextInstruction();
}
