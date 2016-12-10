#include "goto.h"
#include "scheme_integer.h"
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
        cout << "Goto(reg " << this->index->name() << ")" << endl;
        SchemeInteger* registerIndex = dynamic_cast<SchemeInteger *>(this->index->get());
        this->machine_feedback->forceInstruction(registerIndex->asInt());
    } else {
        cout << "Goto(" << this->labelIndex << ")" << endl;
        this->machine_feedback->forceInstruction(this->labelIndex);
    }
}
