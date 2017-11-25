#include "../src/linkage.h"
#include "../src/instruction_sequence.h"
#include <gtest/gtest.h>
 
TEST(LinkageTest, Next) { 
    Linkage* linkage = new LinkageNext();

    ASSERT_EQ(
        *InstructionSequence::empty(),
        *linkage->compile()
    );
}
