#include "assign.h"
#include <iostream>
using namespace std;

Assign::Assign(Register* register_, Operation* operation, std::vector<Value*> operands, Machine* machine)
{
    this->register_ = register_;
    this->operation = operation;
    this->operands = operands;
    this->machine = machine;
}

void Assign::execute()
{
    cout << "Assign (" << this->register_->name() << "): " << this->operation->toString() << endl;
    // only 0-argument supported for now
    auto elements = std::vector<Value*>();
    Value* result = this->operation->execute(elements);
    this->register_->set(result);
}
