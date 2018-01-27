#include "string"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/integer.h"
#include "../src/symbol.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ConsTest, FromStringAndToString) { 
    auto zero_elements = new Nil();
    ASSERT_EQ("NIL", zero_elements->to_string());

    auto one_element = Cons::from_vector({ new Integer(1) });
    ASSERT_EQ("(1)", one_element->to_string());

    auto two_elements = Cons::from_vector({ new Integer(1), new Integer(2) });
    ASSERT_EQ("(1 2)", two_elements->to_string());

    auto three_elements = Cons::from_vector({ new Integer(1), new Integer(2), new Integer(3) });
    ASSERT_EQ("(1 2 3)", three_elements->to_string());

    auto pair = new Cons(new Symbol("year"), new Integer(2017));
    ASSERT_EQ("(year . 2017)", pair->to_string());
}

TEST(ConsTest, ToVector) {
    // needs Nil->to_vector()? and a common superclass?
    //auto list0 = (Cons*) Cons::from_vector({});
    //ASSERT_EQ(0, list0->to_vector().size());
    
    auto list1 = (Cons*) Cons::from_vector({ new Integer(1) });
    ASSERT_EQ(1, list1->to_vector().size());
    auto list2 = (Cons*) Cons::from_vector({ new Integer(1), new Integer(2) });
    ASSERT_EQ(2, list2->to_vector().size());
}

TEST(ConsTest, AppendValue) { 
    auto list = (Cons*) Cons::from_vector({ new Integer(1) });
    auto expanded = list->append(new Integer(2));
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(1), new Integer(2) }),
        *expanded
    );

    list = (Cons*) Cons::from_vector({ new Integer(1), new Integer(2) });
    expanded = list->append(new Integer(3));
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(1), new Integer(2), new Integer(3) }),
        *expanded
    );
}
