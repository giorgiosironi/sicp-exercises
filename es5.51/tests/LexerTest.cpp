#include <vector>
#include <string>
#include <tuple>
#include "../src/lexer.h"
#include <gtest/gtest.h>
using namespace std;
using ::testing::TestWithParam;
using ::testing::Values;
 
// https://github.com/google/googletest/blob/master/googletest/samples/sample7_unittest.cc
class LexerTest : public ::testing::TestWithParam<tuple<string,vector<string>>> {
    public:
        virtual void SetUp() { sample = GetParam(); }

    protected:
        tuple<string,vector<string>> sample;
};

TEST_P(LexerTest, Something) {
    ASSERT_EQ(sample, sample);
    Lexer* lexer = new Lexer();
    ASSERT_EQ(
        get<1>(sample),
        lexer->tokenize(get<0>(sample))
    );
}

INSTANTIATE_TEST_CASE_P(
    Atoms,
    LexerTest,
    Values(
        make_tuple(string("3"), vector<string>({ string("3") })),
        make_tuple(string("foo"), vector<string>({ string("foo") })),
        make_tuple(string("bar"), vector<string>({ string("bar") })),
        make_tuple(string("an-atom"), vector<string>({ string("an-atom") }))
    )
);

