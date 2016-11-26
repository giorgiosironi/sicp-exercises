#include "test.h"
#include <iostream>
using namespace std;

Test::Test(Register* targetRegister, Operation* operation, std::vector<Value*> operands, MachineFeedback* machine)
{
    this->targetRegister = targetRegister;
    this->operation = operation;
    this->operands = operands;
    this->machine_feedback = machine;
}

void Test::execute()
{
    if (this->operation != NULL) {
        Value* result = this->operation->execute(this->operands);
        cout << "Test: " << result->toString() << endl;
        this->targetRegister->set(result);
    } else {
        cout << "Operation is null for Test " << endl;
        exit(1);
    }
    this->machine_feedback->nextInstruction();
}
