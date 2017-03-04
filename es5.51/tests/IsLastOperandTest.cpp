#include "../src/is_last_operand.h"
#include "../src/cons.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
 
TEST(IsLastOperandTest, ListOfOperands) { 
    IsLastOperand* operation = new IsLastOperand();

    ASSERT_EQ(Bool(true), *operation->execute({ Cons::fromVector({ new Integer(1) }) }));
    ASSERT_EQ(Bool(false), *operation->execute({ Cons::fromVector({}) }));
    ASSERT_EQ(Bool(false), *operation->execute({ Cons::fromVector({ new Integer(2), new Integer(1), })}));
}
