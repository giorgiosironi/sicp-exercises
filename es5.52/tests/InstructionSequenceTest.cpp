#include "../src/instruction_sequence.h"
#include "../src/nil.h"
#include "../src/cons.h"
#include "../src/symbol.h"
#include "../src/integer.h"
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

    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("exp") }),
            vector<Symbol*>(),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                })
            })
        ),
        InstructionSequence(
            vector<Symbol*>({ new Symbol("exp") }),
            vector<Symbol*>(),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                })
            })
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

TEST(InstructionSequenceTest, Empty) { 
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>(),
            NIL
        ),
        *InstructionSequence::empty()
    );
}

TEST(InstructionSequenceTest, PreservingARegister) { 
    auto original = new InstructionSequence(
        vector<Symbol*>({}),
        vector<Symbol*>({ new Symbol("val") }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("val"),
                Cons::from_vector({
                    new Symbol("const"),
                    new Integer(42)
                })
            })
        })
    );
    auto followUp = new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>({ new Symbol("exp") }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("exp"),
                Cons::from_vector({
                    new Symbol("const"),
                    new Integer(42)
                })
            })
        })
    );
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>(),
            NIL
        ),
        *original->preserving(
            vector<Symbol*>({ new Symbol("val") }),
            followUp
        )
    );
}
