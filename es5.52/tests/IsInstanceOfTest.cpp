#include "../src/is_instance_of.h"
#include "../src/cons.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
 
TEST(IsInstanceOfTest, Cons) { 
    IsInstanceOf<Cons>* operation = new IsInstanceOf<Cons>();

    ASSERT_EQ(Bool(false), *operation->execute({ new Integer(1) }));
    ASSERT_EQ(Bool(true), *operation->execute({ Cons::from_vector({ new Integer(1) }) }));
}
