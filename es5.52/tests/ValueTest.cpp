#include "string"
#include "../src/value.h"
#include "../src/bool.h"
#include "../src/cons.h"
#include "../src/integer.h"
#include "../src/nil.h"
#include "../src/string.h"
#include "../src/symbol.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ValueTest, Equality) { 
    ASSERT_EQ(Integer(42), Integer(42));
    ASSERT_EQ(String("hello"), String("hello"));
    ASSERT_EQ(Symbol("exp"), Symbol("exp"));
    ASSERT_EQ(Bool(true), Bool(true));
    ASSERT_EQ(Nil(), Nil());
    ASSERT_EQ(Cons(new Integer(42), new Nil()), Cons(new Integer(42), new Nil()));
}

TEST(ValueTest, Inequality) { 
    Value* integer42 = new Integer(42);
    Value* string42 = new String("42");
    ASSERT_NE(*integer42, *string42);
    Value* integer41 = new Integer(41);
    ASSERT_NE(*integer41, *integer42);
    ASSERT_NE(String("hello"), String("world"));
    ASSERT_NE(Symbol("exp"), Symbol("val"));
    ASSERT_NE(Bool(true), Bool(false));
    ASSERT_NE(Cons(new Integer(43), new Nil()), Cons(new Integer(42), new Nil()));
}

