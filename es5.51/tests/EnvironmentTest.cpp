#include "vector"
#include "string"
#include "../src/environment.h"
#include "../src/integer.h"
#include "../src/symbol.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(EnvironmentTest, Empty) { 
    Environment* env = new Environment();
    Value* exp = env->lookup(new Symbol("foo"));
    ASSERT_EQ(NULL, exp);
}

TEST(EnvironmentTest, FrameWithAVariable) { 
    Environment* parent = new Environment();
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    Value* exp = env->lookup(new Symbol("foo"));
    ASSERT_EQ("42", exp->toString());
}

TEST(EnvironmentTest, FrameWithManyVariables) { 
    Environment* parent = new Environment();
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo"), new Symbol("bar"), new Symbol("baz") },
        { new Integer(42), new Integer(43), new Integer(44) }
    ));
    ASSERT_EQ("42", env->lookup(new Symbol("foo"))->toString());
    ASSERT_EQ("43", env->lookup(new Symbol("bar"))->toString());
    ASSERT_EQ("44", env->lookup(new Symbol("baz"))->toString());
}

TEST(EnvironmentTest, MultipleFrames) { 
    Environment* grandparent = new Environment();
    Environment* parent = grandparent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    Environment* env = parent->extend(new Frame(
        { new Symbol("bar"), new Symbol("baz") },
        { new Integer(43), new Integer(44) }
    ));
    ASSERT_EQ("42", env->lookup(new Symbol("foo"))->toString());
    ASSERT_EQ("43", env->lookup(new Symbol("bar"))->toString());
    ASSERT_EQ("44", env->lookup(new Symbol("baz"))->toString());
}

TEST(EnvironmentTest, MultipleFramesShadowing) { 
    Environment* grandparent = new Environment();
    Environment* parent = grandparent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(42) }
    ));
    Environment* env = parent->extend(new Frame(
        { new Symbol("foo") },
        { new Integer(43) }
    ));
    ASSERT_EQ("43", env->lookup(new Symbol("foo"))->toString());
}
