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

TEST(ReadTest, StringEmpty) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("\"\"");
    ASSERT_EQ("\"\"", exp->toString());
}

TEST(ReadTest, StringLong) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("\"foo\"");
    ASSERT_EQ("\"foo\"", exp->toString());
}

TEST(ReadTest, BoolTrue) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("#t");
    ASSERT_EQ("#t", exp->toString());
}

TEST(ReadTest, BoolFalse) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("#f");
    ASSERT_EQ("#f", exp->toString());
}

TEST(ReadTest, ListEmpty) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("()");
    ASSERT_EQ("NIL", exp->toString());
}

TEST(ReadTest, ListOneElement) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1)");
    ASSERT_EQ("(1)", exp->toString());
}

TEST(ReadTest, ListTwoElements) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1 2)");
    ASSERT_EQ("(1 2)", exp->toString());
}

TEST(ReadTest, ListMixedElements) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1 \"foo\")");
    ASSERT_EQ("(1 \"foo\")", exp->toString());
}

TEST(ReadTest, ListNested) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1 (2 3))");
    ASSERT_EQ("(1 (2 3))", exp->toString());
}
