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

TEST(InstructionSequenceTest, Needs) { 
    auto sequence = new InstructionSequence(
        vector<Symbol*>({ new Symbol("val") }),
        vector<Symbol*>(),
        NIL
    );
    ASSERT_EQ(true, sequence->needs(new Symbol("val")));
    ASSERT_EQ(false, sequence->needs(new Symbol("exp")));
}

TEST(InstructionSequenceTest, Modifies) { 
    auto sequence = new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>({ new Symbol("val") }),
        NIL
    );
    ASSERT_EQ(true, sequence->modifies(new Symbol("val")));
    ASSERT_EQ(false, sequence->modifies(new Symbol("exp")));
}

TEST(InstructionSequenceTest, Append) { 
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
        vector<Symbol*>({ new Symbol("val") }),
        vector<Symbol*>({ new Symbol("exp") }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("exp"),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("val")
                })
            })
        })
    );
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("val") }),
            vector<Symbol*>({ new Symbol("val"), new Symbol("exp") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("exp"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    })
                })
            })
        ),
        *original->append(followUp)
    );
}


TEST(InstructionSequenceTest, PreservingWithNoRegisters) { 
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
            vector<Symbol*>({ new Symbol("val"), new Symbol("exp") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("exp"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                })
            })
        ),
        *original->preserving(
            vector<Symbol*>({}),
            followUp
        )
    );
}

TEST(InstructionSequenceTest, PreservingAnUntouchedRegister) { 
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
            vector<Symbol*>({ new Symbol("val"), new Symbol("exp") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("exp"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                })
            })
        ),
        *original->preserving(
            vector<Symbol*>({ new Symbol("env") }),
            followUp
        )
    );
}

TEST(InstructionSequenceTest, PreservingAUsedRegister) { 
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
        vector<Symbol*>({ new Symbol("val") }),
        vector<Symbol*>({ new Symbol("exp") }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("exp"),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("val")
                })
            })
        })
    );
    ASSERT_EQ(
        InstructionSequence(
            vector<Symbol*>({ new Symbol("val") }),
            vector<Symbol*>({ new Symbol("exp") }),
            Cons::from_vector({
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("val"),
                    Cons::from_vector({
                        new Symbol("const"),
                        new Integer(42)
                    })
                }),
                Cons::from_vector({
                    new Symbol("assign"),
                    new Symbol("exp"),
                    Cons::from_vector({
                        new Symbol("reg"),
                        new Symbol("val"),
                    })
                })
            })
        ),
        *original->preserving(
            vector<Symbol*>({ new Symbol("val") }),
            followUp
        )
    );
}
