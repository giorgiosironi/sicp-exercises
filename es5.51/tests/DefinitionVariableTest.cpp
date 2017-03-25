#include "../src/definition_variable.h"
#include "../src/symbol.h"
#include "../src/integer.h"
#include "../src/cons.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(DefinitionVariable, Symbol) { 
    DefinitionVariable* operation = new DefinitionVariable();
    Value* exp = operation->execute({
        Cons::fromVector({
            new Symbol("define"),
            new Symbol("x"),
            new Integer(42),
        })
    });
    ASSERT_EQ(Symbol("x"), *exp);
}

