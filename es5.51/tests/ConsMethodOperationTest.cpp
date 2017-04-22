#include "../src/cons_method_operation.h"
#include "../src/integer.h"
#include <stdexcept>
#include <gtest/gtest.h>
 
TEST(ConsMethodOperationTest, CarOnTwoElementsList) { 
    Value* (Cons::*method_to_call)() = NULL;   
    method_to_call = &Cons::car;
    Cons* list = (Cons*) Cons::from_vector({ new Integer(1), new Integer(2) });

    ASSERT_EQ("1", list->car()->to_string());
    auto operation = ConsMethodOperation::car();
    ASSERT_EQ("1", operation->execute({ list })->to_string());
}

TEST(ConsMethodOperationTest, CarEmptyList) { 
    Value* (Cons::*method_to_call)() = NULL;   
    method_to_call = &Cons::car;
    Cons* list = (Cons*) Cons::from_vector({ });

    auto operation = ConsMethodOperation::car();
    ASSERT_THROW(
        operation->execute({ list })->to_string(),
        std::invalid_argument
    );
}
