#include "vector"
#include "../src/is_tagged_list.h"
#include "../src/symbol.h"
#include "../src/integer.h"
#include "../src/cons.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(IsTaggedList, RelevantTag) { 
    IsTaggedList* operation = new IsTaggedList(new Symbol("set!"));
    Value* exp = operation->execute({ new Cons(new Symbol("set!"), new Integer(42)) });
    ASSERT_EQ("#t", exp->to_string());
}

TEST(IsTaggedList, AnotherTag) { 
    IsTaggedList* operation = new IsTaggedList(new Symbol("set!"));
    Value* exp = operation->execute({ new Cons(new Symbol("quote"), new Integer(42)) });
    ASSERT_EQ("#f", exp->to_string());
}
