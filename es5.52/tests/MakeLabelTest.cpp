#include "string"
#include "../src/make_label.h"
#include "mock_machine_feedback.h"
#include <gtest/gtest.h>

using namespace std;
 
TEST(MakeLabelTest, SequentialValues) { 
    MakeLabel my;
    ASSERT_EQ(
        Symbol("foo1"),
        *my.next("foo")
    );
    ASSERT_EQ(
        Symbol("bar2"),
        *my.next("bar")
    );
    ASSERT_EQ(
        Symbol("baz3"),
        *my.next("baz")
    );
}
