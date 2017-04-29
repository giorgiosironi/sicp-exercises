#include "vector"
#include "string"
#include "../src/read.h"
#include "../src/value.h"
#include "../src/integer.h"
#include "../src/float.h"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/bool.h"
#include "../src/symbol.h"
#include "../src/string.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ReadTest, Integer) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("3");
    ASSERT_EQ(Integer(3), *exp);
}

TEST(ReadTest, Float) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("3.14");
    ASSERT_EQ(Float(3.14), *exp);
}

TEST(ReadTest, BoolTrue) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("#t");
    ASSERT_EQ(Bool(true), *exp);
}

TEST(ReadTest, BoolFalse) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("#f");
    ASSERT_EQ(Bool(false), *exp);
}

TEST(ReadTest, Symbol) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("foo");
    ASSERT_EQ(Symbol("foo"), *exp);
}

TEST(ReadTest, Quoted) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("'foo");
    ASSERT_EQ(
        *(Cons::from_vector({
            new Symbol("quote"), 
            new Symbol("foo"),
        })),
        *exp
    );
}

//TEST(ReadTest, QuotedList) { 
//    Read* instruction = new Read();
//    Value* exp = instruction->parse("'(1 2)");
//    cout << exp->to_string() << endl;
//    ASSERT_EQ(
//        *(Cons::from_vector({
//            new Symbol("quote"), 
//            Cons::from_vector({
//                new Integer(1),
//                new Integer(2),
//            }),
//        })),
//        *exp
//    );
//}

TEST(ReadTest, StringEmpty) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("\"\"");
    ASSERT_EQ(String(""), *exp);
}

TEST(ReadTest, StringLong) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("\"foo\"");
    ASSERT_EQ(String("foo"), *exp);
}

TEST(ReadTest, ListEmpty) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("()");
    ASSERT_EQ(*NIL, *exp);
}

TEST(ReadTest, ListOneElement) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1)");
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(1) }),
        *exp
    );
}

TEST(ReadTest, ListTwoElements) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1 2)");
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(1), new Integer(2) }),
        *exp
    );
}

TEST(ReadTest, ListMixedElements) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1 \"foo\")");
    ASSERT_EQ(
        *Cons::from_vector({ new Integer(1), new String("foo") }),
        *exp
    );
}

TEST(ReadTest, ListNested) { 
    Read* instruction = new Read();
    Value* exp = instruction->parse("(1 (2 3))");
    ASSERT_EQ(
        *Cons::from_vector({
            new Integer(1),
            Cons::from_vector({
                new Integer(2),
                new Integer(3),
            }),
        }),
        *exp
    );
}
