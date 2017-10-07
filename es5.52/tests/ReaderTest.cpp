#include <vector>
#include <string>
#include <tuple>
#include "../src/reader.h"
#include "../src/value.h"
#include "../src/symbol.h"
#include "../src/cons.h"
#include "../src/nil.h"
#include "../src/integer.h"
#include "../src/bool.h"
#include "../src/string.h"
#include "../src/float.h"
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

INSTANTIATE_TEST_CASE_P(
    ListWithOneAtom,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "(", "foo", ")" }),
        (Value*) Cons::from_vector({ Cons::from_vector({ new Symbol("foo") }) })
    ))
);

INSTANTIATE_TEST_CASE_P(
    ListWithTwoAtoms,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "(", "foo", "bar", ")" }),
        (Value*) Cons::from_vector({ Cons::from_vector({ new Symbol("foo"), new Symbol("bar") }) })
    ))
);

INSTANTIATE_TEST_CASE_P(
    ListWithThreeAtoms,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "(", "foo", "bar", "baz", ")" }),
        (Value*) Cons::from_vector({ Cons::from_vector({ new Symbol("foo"), new Symbol("bar"), new Symbol("baz") }) })
    ))
);

INSTANTIATE_TEST_CASE_P(
    FunctionApplication,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "(", "+", "1", "2", ")" }),
        (Value*) Cons::from_vector({ Cons::from_vector({ new Symbol("+"), new Integer(1), new Integer(2) }) })
    ))
);

INSTANTIATE_TEST_CASE_P(
    MixedTypeList,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "(", "\"foo\"", "1.0", "#f", ")" }),
        (Value*) Cons::from_vector({ Cons::from_vector({ new String("foo"), new Float(1.0), new Bool(false) }) })
    ))
);

INSTANTIATE_TEST_CASE_P(
    QuotedAtom,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "'", "foo" }),
        (Value*) Cons::from_vector({ Cons::from_vector({ new Symbol("quote"), new Symbol("foo") }) })
    ))
);

INSTANTIATE_TEST_CASE_P(
    QuotedList,
    ReaderTest,
    Values(make_tuple(
        vector<string>({ "'", "(", "foo", ")" }),
		// TODO: reformat
        (Value*) Cons::from_vector({ Cons::from_vector({ new Symbol("quote"), Cons::from_vector({ new Symbol("foo") }) }) })
    ))
);
