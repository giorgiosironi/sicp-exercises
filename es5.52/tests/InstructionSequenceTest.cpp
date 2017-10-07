#include "../src/instruction_sequence.h"
#include "../src/nil.h"
#include "../src/cons.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(InstructionSequenceTest, Equality) { 
    auto s = new InstructionSequence(vector<Symbol*>(), vector<Symbol*>(), NIL);
    ASSERT_EQ(*s, *s);
    ASSERT_EQ(
        *s,
        InstructionSequence(vector<Symbol*>(), vector<Symbol*>(), NIL)
    );
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("exp") }),
            vector<Symbol*>(),
            NIL
        ),
        InstructionSequence(
            vector<Symbol*>({ new Symbol("exp") }),
            vector<Symbol*>(),
            NIL
        )
    );
}

TEST(InstructionSequenceTest, Inequality) { 
    ASSERT_NE(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("exp") }),
            vector<Symbol*>(),
            NIL
        ),
        InstructionSequence(
            vector<Symbol*>({ new Symbol("val") }),
            vector<Symbol*>(),
            NIL
        )
    );
    ASSERT_NE(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("exp") }),
            NIL
        ),
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("val") }),
            NIL
        )
    );
    ASSERT_NE(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>(),
            NIL
        ),
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>(),
            Cons::from_vector({ new Symbol("perform") })
        )
    );
}
