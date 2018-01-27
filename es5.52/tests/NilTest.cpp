#include "string"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>

using namespace std;
 
TEST(NilTest, AppendValue) { 
    auto expanded = NIL->append(new Integer(2));
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(2) }),
        *expanded
    );
}

TEST(NilTest, AppendList) {
    auto expanded = NIL->append_list(Cons::from_vector({ new Integer(1) }));
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(1) }),
        *expanded
    );
}

TEST(NilTest, Car) {  
    ASSERT_ANY_THROW(NIL->car());
}

