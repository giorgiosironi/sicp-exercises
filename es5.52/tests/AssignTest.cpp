#include "../src/assign.h"
#include "../src/register.h"
#include "../src/integer.h"
#include "../src/symbol.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
 
TEST(AssignTest, ConstantValue) { 
    MockMachineFeedback* m = new MockMachineFeedback();
    Register* r = new Register("continue");
    Assign* instruction = new Assign(r, new Integer(4), m);
    instruction->execute();
}

// TODO: not sure this is needed
TEST(AssignTest, Label) { 
    MockMachineFeedback* m = new MockMachineFeedback();
    Register* r = new Register("continue");
    Assign* instruction = new Assign(r, new Symbol("my-label"), m);
    instruction->execute();
}
