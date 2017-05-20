#include <vector>
#include <string>
#include <tuple>
#include "../src/reader.h"
#include "../src/value.h"
#include "../src/symbol.h"
#include "../src/cons.h"
#include "../src/nil.h"
#include <iostream>
#include <gtest/gtest.h>
using namespace std;
using ::testing::TestWithParam;
using ::testing::Values;
 
// https://github.com/google/googletest/blob/master/googletest/samples/sample7_unittest.cc
class ReaderTest : public ::testing::TestWithParam<tuple<vector<string>,Value*>> {
    public:
        virtual void SetUp() { sample = GetParam(); }

    protected:
        tuple<vector<string>,Value*> sample;
};

TEST_P(ReaderTest, Tokenizing) {
    Reader* reader = new Reader();
    auto expected = get<1>(sample);
    auto actual = reader->parse(get<0>(sample));
    ASSERT_EQ(
        *expected,
        *actual
    ) << "Expected: " << expected->to_string() << endl << "Actual: " << actual->to_string() << endl;
}

INSTANTIATE_TEST_CASE_P(
    Atoms,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "foo" }),
        (Value*) Cons::from_vector({ new Symbol("foo") })
    ))
);

INSTANTIATE_TEST_CASE_P(
    EmptyList,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "(", ")" }),
        (Value*) Cons::from_vector({ NIL })
    ))
);
