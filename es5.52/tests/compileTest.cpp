#include "../src/compile.h"
#include "../src/integer.h"
#include "../src/instruction_sequence.h"
#include "../src/cons.h"
#include <gtest/gtest.h>
 
TEST(compileTest, SelfEvaluating) { 
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42),
                    })
                })
            })
        ),
        *compile(new Integer(42), new Symbol("val"))
    );
}
