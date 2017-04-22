#include "../src/restore.h"
#include "../src/symbol.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
 
TEST(RestoreTest, ValueFromRegister) { 
    Stack* s = new Stack();
    Register* r = new Register("continue");
    MockMachineFeedback* m = new MockMachineFeedback();
    Restore* instruction = new Restore(s, r, m);

    s->push(new Symbol("ev-dispatch"));
    instruction->execute();

    ASSERT_EQ(0, s->size());
    ASSERT_EQ("'ev-dispatch", r->get()->to_string());
    ASSERT_EQ(1, m->get_pc());
}
