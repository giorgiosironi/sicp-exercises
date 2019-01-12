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
        cerr << "[e] " << "Assign (" << this->register_->name() << "): " << this->operation->to_string() << endl;
        Value* result = this->operation->execute(this->fetch_operands(this->operands));
        cout << "[e] " << "Assign result: " << result->to_string() << endl;
        this->register_->set(result);
    } else if (this->value != NULL) {
        cerr << "[e] " << "Assign (" << this->register_->name() << "): " << this->value->to_string() << endl;
        this->register_->set(this->value);
    } else if (this->source != NULL) {
        cerr << "[e] " << "Assign (" << this->register_->name() << "): " << this->source->name() << " == " << this->source->get()->to_string() << endl;
        this->register_->set(this->source->get());
    } else {
        throw logic_error("Assign (" + this->register_->name() + "): invalid instruction");
    }
    this->machine_feedback->next_instruction();
}
