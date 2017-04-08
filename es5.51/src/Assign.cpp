#include "assign.h"
#include <iostream>
using namespace std;

Assign::Assign(Register* register_, Operation* operation, std::vector<Value*> operands, MachineFeedback* machine)
{
    this->register_ = register_;
    this->operation = operation;
    this->operands = operands;
    this->value = NULL;
    this->source = NULL;
    this->machine_feedback = machine;
}

Assign::Assign(Register* register_, Value* value, MachineFeedback *machine)
{
    this->register_ = register_;
    this->operation = NULL;
    this->value = value;
    this->source = NULL;
    this->machine_feedback = machine;
}

Assign::Assign(Register* register_, Register* source, MachineFeedback *machine)
{
    this->register_ = register_;
    this->operation = NULL;
    this->value = NULL;
    this->source = source;
    this->machine_feedback = machine;
}

void Assign::execute()
{
    if (this->operation != NULL) {
        // only 0-argument supported for now
        //auto elements = std::vector<Value*>();
        //Value* result = this->operation->execute(elements);
        Value* result = this->operation->execute(this->fetch_operands(this->operands));
        cerr << "Assign (" << this->register_->name() << "): " << this->operation->toString() << " == " << result->toString() << endl;
        this->register_->set(result);
    } else if (this->value != NULL) {
        cerr << "Assign (" << this->register_->name() << "): " << this->value->toString() << endl;
        this->register_->set(this->value);
    } else if (this->source != NULL) {
        cerr << "Assign (" << this->register_->name() << "): " << this->source->name() << " == " << this->source->get()->toString() << endl;
        this->register_->set(this->source->get());
    } else {
        throw logic_error("Assign (" + this->register_->name() + "): invalid instruction");
    }
    this->machine_feedback->nextInstruction();
}
