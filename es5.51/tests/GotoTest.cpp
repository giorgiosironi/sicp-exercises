#include "../src/goto.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
 
TEST(GotoTest, FixedInstructionIndex) { 
    MockMachineFeedback* m = new MockMachineFeedback();
    Goto* instruction = new Goto(m, 3);
    instruction->execute();
    ASSERT_EQ(3, m->get_pc());
}
 
