#include "../src/extend_environment.h"
#include "../src/symbol.h"
#include "../src/integer.h"
#include "../src/environment.h"
#include "../src/cons.h"
#include <gtest/gtest.h>
using namespace std;
 
TEST(ExtendEnvironmentTest, CoupleOfParameters) { 
    ExtendEnvironment* operation = new ExtendEnvironment();
    Environment* extended = dynamic_cast<Environment*>(operation->execute({
        Cons::from_vector({
            new Symbol("x"),
            new Symbol("y"),
        }),
        Cons::from_vector({
            new Integer(40),
            new Integer(2),
        }),
        new Environment()
    }));
    ASSERT_FALSE(extended == NULL);
    ASSERT_EQ(Integer(40), *extended->lookup(new Symbol("x")));
    ASSERT_EQ(Integer(2), *extended->lookup(new Symbol("y")));
}
