#include "test.h"
#include <iostream>
using namespace std;

Test::Test(Register* targetRegister, Operation* operation, std::vector<Value*> operands, Machine* machine)
{
    this->targetRegister = targetRegister;
    this->operation = operation;
    this->operands = operands;
    this->machine = machine;
}

void Test::execute()
{
    //if (this->operation != NULL) {
    //    cout << "Test (" << this->register_->name() << "): " << this->operation->toString() << endl;
    //    // only 0-argument supported for now
    //    auto elements = std::vector<Value*>();
    //    Value* result = this->operation->execute(elements);
    //    this->register_->set(result);
    //} else if (this->label != NULL) {
    //    cout << "Test (" << this->register_->name() << "): " << this->label->toString() << endl;
    //    this->register_->set(this->label);
    //} else {
        cout << "Test (" << this->targetRegister->name() << ")" << endl;
    //    exit(1);
    //}
    this->machine->nextInstruction();
}
