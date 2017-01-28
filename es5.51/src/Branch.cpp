#include "branch.h"
#include "bool.h"
#include <iostream>
using namespace std;

Branch::Branch(Register* test, MachineFeedback* machine, int labelIndex)
{
    this->test = test;
    this->machine_feedback = machine;
    this->labelIndex = labelIndex;
}

void Branch::execute()
{
    Value* result = this->test->get();
    bool do_we_branch = (dynamic_cast<Bool *>(result))->isTrue();
    cout << "Branch(" << this->labelIndex << "): " << (do_we_branch ? "#t" : "#f") << endl;
    if (do_we_branch) {
        this->machine_feedback->forceInstruction(this->labelIndex);
    } else {
        this->machine_feedback->nextInstruction();
    }
}
