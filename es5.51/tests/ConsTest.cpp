#include "string"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ConsTest, ToString) { 
    auto zero_elements = new Nil();
    ASSERT_EQ("NIL", zero_elements->toString());

    auto one_element = new Cons(new Integer(1), new Nil());
    ASSERT_EQ("(1)", one_element->toString());

    auto two_elements = new Cons(new Integer(1), new Cons(new Integer(2), new Nil()));
    ASSERT_EQ("(1 2)", two_elements->toString());

    auto three_elements = new Cons(new Integer(1), new Cons(new Integer(2), new Cons(new Integer(3), new Nil())));
    ASSERT_EQ("(1 2 3)", three_elements->toString());
}

TEST(ConsTest, Append) { 
    auto list = new Cons(new Integer(1), new Nil());
    auto expanded = list->append(new Integer(2));
    ASSERT_EQ("(1 2)", expanded->toString());

    list = new Cons(new Integer(1), new Cons(new Integer(2), new Nil()));
    expanded = list->append(new Integer(3));
    ASSERT_EQ("(1 2 3)", expanded->toString());
}
