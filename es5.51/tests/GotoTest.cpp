#include "../src/goto.h"
#include "../src/register.h"
#include "../src/scheme_integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
 
TEST(GotoTest, FixedInstructionIndex) { 
    MockMachineFeedback* m = new MockMachineFeedback();
    Goto* instruction = new Goto(m, 3);
    instruction->execute();
    ASSERT_EQ(3, m->get_pc());
}

TEST(GotoTest, RegisterContainingTheInstructionIndex) { 
    MockMachineFeedback* m = new MockMachineFeedback();
    Register* r = new Register("continue");
    r->set(new SchemeInteger(4));
    Goto* instruction = new Goto(m, r);
    instruction->execute();
    ASSERT_EQ(4, m->get_pc());
}
 
