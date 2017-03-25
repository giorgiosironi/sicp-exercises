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
        Cons::fromVector({
            new Symbol("define"),
            new Symbol("x"),
            new Integer(42),
        })
    });
    ASSERT_EQ(Integer(42), *exp);
}

TEST(DefinitionValueTest, NamedProcedure) { 
    DefinitionValue* operation = new DefinitionValue();
    auto define = Cons::fromVector({
        new Symbol("define"),
        Cons::fromVector({
            new Symbol("inc"),
            new Symbol("x"),
        }),
        Cons::fromVector({
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
                Cons::fromVector({ new Symbol("x") }),
                Cons::fromVector({
                    Cons::fromVector({
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

