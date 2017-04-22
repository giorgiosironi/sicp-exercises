#include "goto.h"
#include "integer.h"
#include <iostream>
using namespace std;

Goto::Goto(MachineFeedback* machine, int labelIndex)
{
    this->machine_feedback = machine;
    this->labelIndex = labelIndex;
    this->index = NULL;
}

Goto::Goto(MachineFeedback* machine, Register* index)
{
    this->machine_feedback = machine;
    this->labelIndex = -1;
    this->index = index;
}

void Goto::execute()
{
    if (this->index != NULL) {
        cerr << "Goto(reg " << this->index->name() << ")" << endl;
        Integer* registerIndex = dynamic_cast<Integer *>(this->index->get());
        this->machine_feedback->force_instruction(registerIndex->as_int());
    } else {
        cerr << "Goto(" << this->labelIndex << ")" << endl;
        this->machine_feedback->force_instruction(this->labelIndex);
    }
}
