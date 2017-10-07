#include "vector"
#include "string"
#include "../src/environment.h"
#include "../src/integer.h"
#include "../src/symbol.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(EnvironmentTest, GetOnEmpty) { 
    Environment* env = new Environment();
    Value* exp = env->lookup(new Symbol("foo"));
    ASSERT_EQ(NULL, exp);
}

TEST(EnvironmentTest, GetInFrameWithAVariable) { 
    Environment* parent = new Environment();
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    Value* exp = env->lookup(new Symbol("foo"));
    ASSERT_EQ(Integer(42), *exp);
}

TEST(EnvironmentTest, GetInFrameWithManyVariables) { 
    Environment* parent = new Environment();
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo"), new Symbol("bar"), new Symbol("baz") },
        { new Integer(42), new Integer(43), new Integer(44) }
    ));
    ASSERT_EQ(Integer(42), *env->lookup(new Symbol("foo")));
    ASSERT_EQ(Integer(43), *env->lookup(new Symbol("bar")));
    ASSERT_EQ(Integer(44), *env->lookup(new Symbol("baz")));
}

TEST(EnvironmentTest, GetWithMultipleFrames) { 
    Environment* grandparent = new Environment();
    Environment* parent = grandparent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    Environment* env = parent->extend(new Frame(
        { new Symbol("bar"), new Symbol("baz") },
        { new Integer(43), new Integer(44) }
    ));
    ASSERT_EQ(Integer(42), *env->lookup(new Symbol("foo")));
    ASSERT_EQ(Integer(43), *env->lookup(new Symbol("bar")));
    ASSERT_EQ(Integer(44), *env->lookup(new Symbol("baz")));
}

TEST(EnvironmentTest, GetWithMultipleFramesShadowing) { 
    Environment* grandparent = new Environment();
    Environment* parent = grandparent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(43) }
    ));
    ASSERT_EQ(Integer(43), *env->lookup(new Symbol("foo")));
}

TEST(EnvironmentTest, SetInFrameWithAVariable) { 
    Environment* parent = new Environment();
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    env->set(new Symbol("foo"), new Integer(43));
    ASSERT_EQ(Integer(43), *env->lookup(new Symbol("foo")));
}

TEST(EnvironmentTest, SetInFrameWithoutAVariable) { 
    Environment* parent = new Environment();
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    env->set(new Symbol("bar"), new Integer(43));
    ASSERT_EQ(Integer(43), *env->lookup(new Symbol("bar")));
}

TEST(EnvironmentTest, SetInMultipleFramesActsOnTheFrameThatContainsTheVariable) { 
    Environment* grandparent = new Environment();
    Frame* lower = new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    );
    Environment* parent = grandparent->extend(lower);
    Frame* upper = new Frame(
        { new Symbol("bar") },
        { new Integer(43) }
    );
    Environment* child = parent->extend(upper);
    child->set(new Symbol("foo"), new Integer(44));
    ASSERT_EQ(Integer(44), *child->lookup(new Symbol("foo")));
    ASSERT_EQ(Integer(44), *lower->lookup(new Symbol("foo")));
}
