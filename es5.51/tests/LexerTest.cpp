#include "vector"
#include "string"
#include "../src/lexer.h"
#include <gtest/gtest.h>
using namespace std;
using ::testing::TestWithParam;
using ::testing::Values;
 
// https://github.com/google/googletest/blob/master/googletest/samples/sample7_unittest.cc
class FooTest : public ::testing::TestWithParam<const char*> {
//       You can implement all the usual fixture class members here.
         // To access the test parameter, call GetParam() from class
           // TestWithParam<T>.
    public:
        //virtual ~FooTest() { delete input; }
        virtual void SetUp() { input = GetParam(); }
        //virtual void TearDown() {
        //    delete input;
        //    input = NULL;
        //}

    protected:
        std::string input;
};

TEST_P(FooTest, Something) {
    ASSERT_EQ(input, input);
    Lexer* lexer = new Lexer();
    ASSERT_EQ(
        vector<string>({ input }),
        lexer->tokenize(input)
    );
}

INSTANTIATE_TEST_CASE_P(
    LexerTest,
    FooTest,
    Values("3", "5")
);

