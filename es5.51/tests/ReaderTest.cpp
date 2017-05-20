#include <vector>
#include <string>
#include <tuple>
#include "../src/reader.h"
#include "../src/value.h"
#include "../src/symbol.h"
#include "../src/cons.h"
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
    ASSERT_EQ(
        *get<1>(sample),
        *reader->parse(get<0>(sample))
    );
}

INSTANTIATE_TEST_CASE_P(
    Atoms,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "foo" }),
        (Value*) Cons::from_vector({ new Symbol("foo") })
    ))
);
