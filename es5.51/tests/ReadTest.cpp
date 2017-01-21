#include "vector"
#include "string"
#include "../src/read.h"
#include "../src/value.h"
#include "../src/integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ReadTest, Integer) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("3");
    ASSERT_EQ("3", exp->toString());
}

TEST(ReadTest, Symbol) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("foo");
    ASSERT_EQ("'foo", exp->toString());
}

TEST(ReadTest, String) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("\"foo\"");
    ASSERT_EQ("\"foo\"", exp->toString());
}
