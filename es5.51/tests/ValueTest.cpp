#include "string"
#include "../src/value.h"
#include "../src/string.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ValueTest, Equality) { 
    ASSERT_EQ(Integer(42), Integer(42));
    ASSERT_EQ(String("hello"), String("hello"));
}

TEST(ValueTest, Inequality) { 
    Value* integer42 = new Integer(42);
    Value* string42 = new String("42");
    ASSERT_NE(*integer42, *string42);
    Value* integer41 = new Integer(41);
    ASSERT_NE(*integer41, *integer42);
    ASSERT_NE(String("hello"), String("world"));
}

