#include "../src/adjoin_arg.h"
#include "../src/cons.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
 
TEST(AdjoinArgTest, ScalarValue) { 
    AdjoinArg* operation = new AdjoinArg();

    ASSERT_EQ(
        *Cons::fromVector({
            new Integer(1),
            new Integer(2),
            new Integer(3),
        }), 
        *operation->execute({
            new Integer(3),
            Cons::fromVector({ new Integer(1), new Integer(2) })
        })
    );
}
