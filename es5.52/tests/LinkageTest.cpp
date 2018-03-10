#include "../src/linkage.h"
#include "../src/instruction_sequence.h"
#include "../src/nil.h"
#include "../src/cons.h"
#include <gtest/gtest.h>
 
TEST(LinkageTest, Next) { 
    Linkage* linkage = new LinkageNext();

    ASSERT_EQ(
        *InstructionSequence::empty(),
        *linkage->compile()
    );
}

TEST(LinkageTest, UseToEndWith) { 
    Linkage* linkage = new LinkageNext();
    List* assignment = Cons::from_vector({
        new Symbol("assign"),
        new Symbol("continue"),
        Cons::from_vector({
            new Symbol("label"),
            new Symbol("foo")
        })
    });

    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("continue") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("save"),
                    new Symbol("continue"),
                }),
                assignment,
                Cons::from_vector({
                    new Symbol("restore"),
                    new Symbol("continue"),
                }),
            })
        ),
        *linkage->use_to_end_with(new InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("continue") }),
            Cons::from_vector({
                assignment
            })
        ))
    );
}
