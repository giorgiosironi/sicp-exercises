#include "vector"
#include "../src/is_tagged_list.h"
#include "../src/symbol.h"
#include "../src/integer.h"
#include "../src/cons.h"
#include "../src/bool.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(IsTaggedListTest, RelevantTag) { 
    IsTaggedList* operation = new IsTaggedList(new Symbol("set!"));
    Value* exp = operation->execute({ new Cons(new Symbol("set!"), new Integer(42)) });
    ASSERT_EQ(Bool(true), *exp);
}

TEST(IsTaggedListTest, AnotherTag) { 
    IsTaggedList* operation = new IsTaggedList(new Symbol("set!"));
    Value* exp = operation->execute({ new Cons(new Symbol("quote"), new Integer(42)) });
    ASSERT_EQ(Bool(false), *exp);
}
