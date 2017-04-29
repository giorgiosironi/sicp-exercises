#include "string"
#include "../src/primitive_plus.h"
#include "../src/integer.h"
#include "../src/cons.h"
#include <gtest/gtest.h>
using namespace std;

TEST(PrimitivePlusTest, ZeroNumbers) { 
    auto op = new PrimitivePlus();
    ASSERT_EQ(
        Integer(0), 
        *op->apply(Cons::from_vector({}))
    );
}

TEST(PrimitivePlusTest, OneNumber) { 
    auto op = new PrimitivePlus();
    ASSERT_EQ(
        Integer(2), 
        *op->apply(Cons::from_vector({ new Integer(2) }))
    );
}
 
TEST(PrimitivePlusTest, TwoNumbers) { 
    auto op = new PrimitivePlus();
    ASSERT_EQ(
        Integer(5), 
        *op->apply(Cons::from_vector({ new Integer(2), new Integer(3) }))
    );
}

TEST(PrimitivePlusTest, ManyNumbers) { 
    auto op = new PrimitivePlus();
    ASSERT_EQ(
        Integer(15), 
        *op->apply(Cons::from_vector({ new Integer(1), new Integer(2), new Integer(3), new Integer(4), new Integer(5) }))
    );
}
