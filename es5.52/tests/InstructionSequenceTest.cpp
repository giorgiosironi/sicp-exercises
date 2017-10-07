#include "../src/instruction_sequence.h"
#include "../src/nil.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(InstructionSequenceTest, Creation) { 
    auto s = new InstructionSequence(vector<Symbol*>(), vector<Symbol*>(), NIL);
}
