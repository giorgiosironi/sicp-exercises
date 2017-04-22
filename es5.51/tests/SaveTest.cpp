#include "../src/save.h"
#include "../src/integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
 
TEST(SaveTest, ValueFromRegister) { 
    Stack* s = new Stack();
    Register* r = new Register("unev");
    MockMachineFeedback* m = new MockMachineFeedback();
    Save* instruction = new Save(s, r, m);

    r->set(new Integer(42));
    instruction->execute();

    ASSERT_EQ(1, s->size());
    ASSERT_EQ("42", s->pop()->to_string());
    ASSERT_EQ(1, m->get_pc());
}
