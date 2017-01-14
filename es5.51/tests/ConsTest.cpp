#include "string"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ConsTest, ToString) { 
    auto one_element = new Cons(new Integer(1), new Nil());
    ASSERT_EQ("(1)", one_element->toString());

    auto two_elements = new Cons(new Integer(1), new Cons(new Integer(2), new Nil()));
    ASSERT_EQ("(1 2)", two_elements->toString());
}

TEST(ConsTest, Append) { 
    auto list = new Cons(new Integer(1), new Nil());
    auto expanded = list->append(new Integer(2));
    ASSERT_EQ("(1 2)", expanded->toString());
}
