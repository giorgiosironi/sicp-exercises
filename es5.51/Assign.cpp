#include "assign.h"
#include <iostream>
using namespace std;

Assign::Assign(Register* register_, Operation* operation, std::vector<Value*> operands, Machine* machine)
{
    this->register_ = register_;
    this->operation = operation;
    this->operands = operands;
    this->label = NULL;
    this->machine = machine;
}

Assign::Assign(Register* register_, Label* label, Machine *machine)
{
    this->register_ = register_;
    this->operation = NULL;
    this->label = label;
    this->machine = machine;
}

void Assign::execute()
{
    if (this->operation != NULL) {
        cout << "Assign (" << this->register_->name() << "): " << this->operation->toString() << endl;
        // only 0-argument supported for now
        auto elements = std::vector<Value*>();
        Value* result = this->operation->execute(elements);
        this->register_->set(result);
    } else if (this->label != NULL) {
        cout << "Assign (" << this->register_->name() << "): " << this->label->toString() << endl;
        this->register_->set(this->label);
    } else {
        cout << "Assign (" << this->register_->name() << "): invalid instruction" << endl;
        exit(1);
    }
    this->machine->nextInstruction();
}
