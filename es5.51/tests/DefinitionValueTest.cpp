#include "../src/definition_value.h"
#include "../src/symbol.h"
#include "../src/integer.h"
#include "../src/cons.h"
    #include "../src/nil.h"
#include "vector"
#include <gtest/gtest.h>
using namespace std;
 
TEST(DefinitionValueTest, SimpleAssignment) { 
    DefinitionValue* operation = new DefinitionValue();
    Value* exp = operation->execute({
        Cons::from_vector({
            new Symbol("define"),
            new Symbol("x"),
            new Integer(42),
        })
    });
    ASSERT_EQ(Integer(42), *exp);
}

TEST(DefinitionValueTest, NamedProcedure) { 
    DefinitionValue* operation = new DefinitionValue();
    auto define = Cons::from_vector({
        new Symbol("define"),
        Cons::from_vector({
            new Symbol("inc"),
            new Symbol("x"),
        }),
        Cons::from_vector({
            new Symbol("+"),
            new Symbol("x"),
            new Integer(1),
        }),
    });
    Value* exp = operation->execute({
        define
    });
    ASSERT_EQ(
        Cons(
            new Symbol("lambda"),
            new Cons(
                Cons::from_vector({ new Symbol("x") }),
                Cons::from_vector({
                    Cons::from_vector({
                        new Symbol("+"),
                        new Symbol("x"),
                        new Integer(1),
                    })
                })
            )
        ),
        *exp
    );
}

