#include "../src/cons_method_operation.h"
#include "../src/integer.h"
#include <gtest/gtest.h>
 
TEST(ConsMethodOperationTest, Car) { 
    Value* (Cons::*method_to_call)() = NULL;   
    method_to_call = &Cons::car;
    Cons* list = (Cons*) Cons::fromVector({ new Integer(1), new Integer(2) });

    ASSERT_EQ("1", list->car()->toString());
    auto operation = ConsMethodOperation::car();
    ASSERT_EQ("1", operation->execute({ list })->toString());
}
