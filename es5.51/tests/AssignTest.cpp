#include "../src/assign.h"
#include "../src/register.h"
#include "../src/scheme_integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
 
TEST(AssignTest, ConstantValue) { 
    MockMachineFeedback* m = new MockMachineFeedback();
    Register* r = new Register("continue");
    Assign* instruction = new Assign(r, new SchemeInteger(4), m);
    instruction->execute();
}

