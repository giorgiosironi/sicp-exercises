#include "vector"
#include "../src/is_equal_to.h"
#include "../src/bool.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(IsEqualToTest, EqualToReference) { 
    IsEqualTo* op = new IsEqualTo(new Bool(true));
    Value* result = op->execute({ new Bool(true) });
    ASSERT_EQ("#t", result->to_string());
}

TEST(IsEqualToTest, AnotherValue) { 
    IsEqualTo* op = new IsEqualTo(new Bool(true));
    Value* result = op->execute({ new Bool(false) });
    ASSERT_EQ("#f", result->to_string());
}

TEST(IsEqualToTest, AnotherValueOfDifferentType) { 
    IsEqualTo* op = new IsEqualTo(new Bool(true));
    Value* result = op->execute({ new Integer(42) });
    ASSERT_EQ("#f", result->to_string());
}

