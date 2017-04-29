#include "vector"
#include "../src/is_not_equal_to.h"
#include "../src/bool.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(IsNotEqualToTest, EqualToReference) { 
    IsNotEqualTo* op = new IsNotEqualTo(new Bool(false));
    Value* result = op->execute({ new Bool(false) });
    ASSERT_EQ(Bool(false), *result);
}

TEST(IsNotEqualToTest, AnotherValue) { 
    IsNotEqualTo* op = new IsNotEqualTo(new Bool(false));
    Value* result = op->execute({ new Bool(true) });
    ASSERT_EQ(Bool(true), *result);
}

TEST(IsNotEqualToTest, AnotherValueOfDifferentType) { 
    IsNotEqualTo* op = new IsNotEqualTo(new Bool(false));
    Value* result = op->execute({ new Integer(42) });
    ASSERT_EQ(Bool(true), *result);
}

