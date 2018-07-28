#include "../src/compile.h"
#include "../src/integer.h"
#include "../src/instruction_sequence.h"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/make_label.h"
#include <gtest/gtest.h>

class compileTest : public testing::Test {
  //virtual void SetUp() {}

  virtual void TearDown() {
	reset_labels();
  }
};

TEST_F(compileTest, SelfEvaluating) { 
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
        *compile(new Integer(42), new Symbol("val"), new LinkageNext())
    );
}

TEST_F(compileTest, Variable) { 
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("env") }),
            vector<Symbol*>({ new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("lookup-variable-value"),
                    }),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Symbol("my-number"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("env"),
                    }),
                })
            })
        ),
        *compile(new Symbol("my-number"), new Symbol("val"), new LinkageNext())
    );
}

TEST_F(compileTest, Quoted) { 
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({}),
            vector<Symbol*>({ new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(2017),
                    }),
                })
            })
        ),
        *compile(
            Cons::from_vector({
                new Symbol("quote"),
                new Integer(2017)
            }),
            new Symbol("val"),
            new LinkageNext()
        )
    );
}

TEST_F(compileTest, DefinitionVariable) { 
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("env"), new Symbol("val") }),
            vector<Symbol*>({ new Symbol("some"), new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("perform"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("define-variable!"),
                    }),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Symbol("answer"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("env"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("some"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Symbol("ok"),
                    }),
                }),
            })
        ),
        *compile(
            Cons::from_vector({
                new Symbol("define"),
                new Symbol("answer"),
                new Integer(42)
            }),
            new Symbol("some"),
            new LinkageNext()
        )
    );
}

TEST_F(compileTest, ApplicationOfPrimitiveProcedure) { 
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("argl"), new Symbol("env"), new Symbol("proc"), new Symbol("val") }),
            vector<Symbol*>({ new Symbol("argl"), new Symbol("continue"), new Symbol("env"), new Symbol("proc"), new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("proc"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("lookup-variable-value"),
                    }),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Symbol("+"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("env"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(2),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("list"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(1),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("cons"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("argl"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("test"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("is-primitive-procedure"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("proc"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("branch"),
                    Cons::from_vector({
                        new Symbol("label"),
                        new Symbol("primitive-branch1"),
                    }),
                }),
                new Symbol("compiled-branch2"),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("continue"),
                    Cons::from_vector({
                        new Symbol("label"),
                        new Symbol("after-call3"),
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
                new Symbol("primitive-branch1"),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("apply-primitive-procedure"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("proc"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("argl"),
                    }),
                }),
                new Symbol("after-call3"),
            })
        ),
        *compile(
            Cons::from_vector({
                new Symbol("+"),
                new Integer(1),
                new Integer(2)
            }),
            new Symbol("val"),
            new LinkageNext()
        )
    );
}

TEST_F(compileTest, construct_arg_list_0_operands) { 
    vector<InstructionSequence*> operandCodes = {};
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("argl") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("const"),
                        NIL
                    })
                })
            })
        ),
        *construct_arg_list(operandCodes)
    );
}

TEST_F(compileTest, construct_arg_list_1_operand) { 
    vector<InstructionSequence*> operandCodes = {
        new InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(1),
                    })
                })
            })
        ),
    };
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("val") }),
            vector<Symbol*>({ new Symbol("argl"), new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(1),
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("list"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    })
                })
            })
        ),
        *construct_arg_list(operandCodes)
    );
}

TEST_F(compileTest, construct_arg_list_2_operand) { 
    vector<InstructionSequence*> operandCodes = {
        new InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(1),
                    })
                })
            })
        ),
        new InstructionSequence(
            vector<Symbol*>(),
            vector<Symbol*>({ new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(2),
                    })
                })
            })
        ),
    };
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("argl"), new Symbol("val") }),
            vector<Symbol*>({ new Symbol("argl"), new Symbol("val") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(2),
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("list"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(1),
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("argl"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("cons"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("argl"),
                    })
                }),
            })
        ),
        *construct_arg_list(operandCodes)
    );
}


// if LinkageNext is used, the target register may or may not be `val`, it doesn't matter
TEST_F(compileTest, compile_procedure_call_target_val_linkage_next) { 
    Symbol* target = new Symbol("val");
    Linkage* linkage = new LinkageNext();
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("argl"), new Symbol("proc") }),
            vector<Symbol*>({ 
                new Symbol("argl"),
                new Symbol("continue"), 
                new Symbol("env"),
                new Symbol("proc"), 
                new Symbol("val"), 
            }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("test"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("is-primitive-procedure"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("proc"),
                    }),
                }),
                Cons::from_vector({
                    new Symbol("branch"),
                    Cons::from_vector({
                        new Symbol("label"),
                        new Symbol("primitive-branch4"),
                    }),
                }),
                new Symbol("compiled-branch5"),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("continue"),
                    Cons::from_vector({
                        new Symbol("label"),
                        new Symbol("after-call6"),
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
                new Symbol("primitive-branch4"),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("op"),
                        new Symbol("apply-primitive-procedure"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("proc"),
                    }),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("argl"),
                    }),
                }),
                new Symbol("after-call6"),
            })
        ),
        *compile_procedure_call(target, linkage)
    );
}

