#include "../src/make_compiled_procedure.h"
#include "../src/cons.h"
#include "../src/integer.h"
#include "../src/symbol.h"
#include "../src/environment.h"
#include <gtest/gtest.h>
 
TEST(MakeCompiledProcedureTest, EntryAndEnv) { 
    MakeCompiledProcedure* operation = new MakeCompiledProcedure();
    Integer* entry = new Integer(42);
    Environment* env = new Environment();

    ASSERT_EQ(
        Cons::from_vector({
            new Symbol("compiled-procedure"),
            entry,
            env,
        })->to_string(),
        operation->execute({
            entry,
            env
        })->to_string()
    );
}

