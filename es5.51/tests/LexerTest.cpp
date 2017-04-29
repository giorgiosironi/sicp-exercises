#include "vector"
#include "string"
#include "../src/lexer.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(LexerTest, Integer) { 
    Lexer* lexer = new Lexer();
    ASSERT_EQ(
        vector<string>({ "3" }),
        lexer->tokenize("3")
    );
}
