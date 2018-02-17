#include "../src/dump.h"
#include "../src/integer.h"
#include "../src/symbol.h"
#include <gtest/gtest.h>

TEST(dumpTest, VectorOfSymbols) { 
    ASSERT_EQ(
        "<val,env>",
        to_string<Symbol>(vector<Symbol*>({ new Symbol("val"), new Symbol("env") }))
    );
}

TEST(dumpTest, VectorOfIntegers) { 
    ASSERT_EQ(
        "<42,43>",
        to_string<Integer>(vector<Integer*>({ new Integer(42), new Integer(43) }))
    );
}

TEST(dumpTest, SetOfIntegers) { 
    ASSERT_EQ(
        "{42,43}",
        to_string<Integer>(set<Integer*>({ new Integer(42), new Integer(43) }))
    );
}

TEST(dumpTest, SetWithDuplicates) { 
    ASSERT_EQ(
        "{42}",
        to_string<Integer>(set<Integer*>({ new Integer(42), new Integer(42) }))
    );
}
