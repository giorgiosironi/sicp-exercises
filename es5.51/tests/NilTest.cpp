#include "string"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/integer.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>

using namespace std;
 
TEST(NilTest, Append) { 
    auto expanded = NIL->append(new Integer(2));
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(2) }),
        *expanded
    );
}

TEST(NilTest, Car) {  
    ASSERT_ANY_THROW(NIL->car());
}
