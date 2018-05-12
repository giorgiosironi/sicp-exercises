#include "../src/compile.h"
#include "../src/integer.h"
#include "../src/instruction_sequence.h"
#include "../src/cons.h"
#include "../src/nil.h"
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
        *compile(new Integer(42), new Symbol("val"), new LinkageNext())
    );
}

TEST(compileTest, Variable) { 
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

TEST(compileTest, Quoted) { 
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

TEST(compileTest, DefinitionVariable) { 
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

TEST(compileTest, ApplicationOfPrimitiveProcedure) { 
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("env")}),
            vector<Symbol*>({ new Symbol("proc")}),
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
                })
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

TEST(compileTest, construct_arg_list_0_operands) { 
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

TEST(compileTest, construct_arg_list_1_operand) { 
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

TEST(compileTest, construct_arg_list_2_operand) { 
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


TEST(compileTest, compile_procedure_call_linkage_next) { 
    Symbol* target = new Symbol("val");
    Linkage* linkage = new LinkageNext();
    ASSERT_EQ(
        *InstructionSequence::empty(),
        *compile_procedure_call(target, linkage)
    );
}

