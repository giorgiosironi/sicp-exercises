#include "save.h"
#include <iostream>
using namespace std;

Save::Save(Stack* stack, Register* register_, MachineFeedback* machine)
{
    this->stack = stack;
    this->register_ = register_;
    this->machine_feedback = machine;
}

void Save::execute()
{
    auto value = this->register_->get();
    cerr << "[e] " << "Save (" << this->register_->name() << "): " << value->to_string() << endl;
    this->stack->push(value);
    this->machine_feedback->next_instruction();
}
