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
        to_string<Integer>(set<Integer>({ Integer(42), Integer(43) }))
    );
}

TEST(dumpTest, SetWithDuplicates) { 
    auto s = set<Integer>();
    s.insert(Integer(42));
    s.insert(Integer(42));
    ASSERT_EQ(1, s.size());
    ASSERT_EQ(
        "{42}",
        to_string<Integer>(s)
    );
}

