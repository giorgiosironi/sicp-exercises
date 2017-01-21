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

    auto one_element = Cons::fromVector({ new Integer(1) });
    ASSERT_EQ("(1)", one_element->toString());

    auto two_elements = Cons::fromVector({ new Integer(1), new Integer(2) });
    ASSERT_EQ("(1 2)", two_elements->toString());

    auto three_elements = Cons::fromVector({ new Integer(1), new Integer(2), new Integer(3) });
    ASSERT_EQ("(1 2 3)", three_elements->toString());
}

TEST(ConsTest, Append) { 
    auto list = (Cons*) Cons::fromVector({ new Integer(1) });
    auto expanded = list->append(new Integer(2));
    ASSERT_EQ("(1 2)", expanded->toString());

    list = (Cons*) Cons::fromVector({ new Integer(1), new Integer(2) });
    expanded = list->append(new Integer(3));
    ASSERT_EQ("(1 2 3)", expanded->toString());
}
