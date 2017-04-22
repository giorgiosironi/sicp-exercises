#include "../src/definition_variable.h"
#include "../src/symbol.h"
#include "../src/integer.h"
#include "../src/cons.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(DefinitionVariable, SimpleAssignment) { 
    DefinitionVariable* operation = new DefinitionVariable();
    Value* exp = operation->execute({
        Cons::from_vector({
            new Symbol("define"),
            new Symbol("x"),
            new Integer(42),
        })
    });
    ASSERT_EQ(Symbol("x"), *exp);
}

TEST(DefinitionVariable, NamedProcedure) { 
    DefinitionVariable* operation = new DefinitionVariable();
    Value* exp = operation->execute({
        Cons::from_vector({
            new Symbol("define"),
            Cons::from_vector({
                new Symbol("identity"),
                new Symbol("x"),
            }),
            new Symbol("x"),
        })
    });
    ASSERT_EQ(Symbol("identity"), *exp);
}

