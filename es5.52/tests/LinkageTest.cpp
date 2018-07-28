#include "../src/linkage.h"
#include "../src/instruction_sequence.h"
#include "../src/nil.h"
#include "../src/cons.h"
#include "../src/make_label.h"
#include <gtest/gtest.h>

class LinkageTest : public testing::Test {

  virtual void TearDown() {
	reset_labels();
  }
};
 
TEST_F(LinkageTest, Next) { 
    Linkage* linkage = new LinkageNext();

    ASSERT_EQ(
        *InstructionSequence::empty(),
        *linkage->compile()
    );
}

TEST_F(LinkageTest, Return) { 
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

TEST_F(LinkageTest, Label) { 
    Linkage* linkage = new LinkageLabel(new Symbol("after-some-if"));

    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>(),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("label"),
                        new Symbol("after-some-if"),
                    })
                })
            })
        ),
        *linkage->compile()
    );
}

TEST_F(LinkageTest, UseToEndWith) { 
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

TEST_F(LinkageTest, CompileProcAppl_TargetVal_Label) { 
    LinkageJump* non_return_linkage = new LinkageLabel(new Symbol("somewhere"));

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
                        new Symbol("somewhere"),
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

TEST_F(LinkageTest, CompileProcAppl_TargetNotVal_Label) { 
    LinkageJump* non_return_linkage = new LinkageLabel(new Symbol("somewhere"));

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
                        // TODO: like for compileTest, reset labels in teardown
                        new Symbol("proc-return1"),
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
                new Symbol("proc-return1"),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("exp"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("goto"),
                    Cons::from_vector({
                        new Symbol("label"),
                        new Symbol("somewhere"),
                    }),
                }),
            })
        ),
        *non_return_linkage->compile_proc_appl(new Symbol("exp"))
    );
}

TEST_F(LinkageTest, CompileProcAppl_TargetVal_Return) { 
    LinkageReturn* return_linkage = new LinkageReturn(); //new Symbol("somewhere"));

    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("continue"), new Symbol("proc") }),
            vector<Symbol*>({ new Symbol("argl"), new Symbol("continue"), new Symbol("env"), new Symbol("proc"), new Symbol("val")}),
            Cons::from_vector({
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
        *return_linkage->compile_proc_appl(new Symbol("val"))
    );
}
