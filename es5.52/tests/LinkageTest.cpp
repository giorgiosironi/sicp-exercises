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

TEST(LinkageTest, Return) { 
    Linkage* linkage = new LinkageReturn();

    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("continue") }),
            vector<Symbol*>(),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("continue"),
                    })
                })
            })
        ),
        *linkage->compile()
    );
}

TEST(LinkageTest, UseToEndWith) { 
    Linkage* linkage = new LinkageReturn();
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
            vector<Symbol*>({ new Symbol("continue") }),
            vector<Symbol*>(),
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
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("continue"),
                    }),
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

TEST(LinkageTest, CompileProcAppl_TargetVal_NonReturn) { 
    Linkage* non_return_linkage = new LinkageNext();

    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("proc") }),
            vector<Symbol*>({ new Symbol("argl"), new Symbol("continue"), new Symbol("env"), new Symbol("proc"), new Symbol("val")}),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("continue"),
                    Cons::from_vector({
                        new Symbol("label"),
                        new Symbol("TODO-should-point-to-a-label?"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("compiled-procedure-entry"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("proc"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                }),
            })
        ),
        *non_return_linkage->compile_proc_appl(new Symbol("val"))
    );
}
