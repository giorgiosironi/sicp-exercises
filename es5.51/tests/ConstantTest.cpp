#include "../src/constant.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
 
TEST(ConstantTest, Cons) { 
    Operation* operation = new Constant(new Integer(1));

    ASSERT_EQ(Integer(1), *operation->execute({}));
}
