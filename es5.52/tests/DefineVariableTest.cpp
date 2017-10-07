#include "../src/define_variable.h"
#include "../src/symbol.h"
#include "../src/integer.h"
#include "../src/environment.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(DefineVariableTest, Scalar) { 
    Operation* operation = new DefineVariable();
    Environment* env = new Environment();
    Value* exp = operation->execute({ 
        new Symbol("answer"),
        new Integer(42),
        env
    });
    ASSERT_EQ(Symbol("ok"), *exp);
    ASSERT_TRUE(NULL != env->lookup(new Symbol("answer")));
    ASSERT_EQ(Integer(42), *(env->lookup(new Symbol("answer"))));
}

