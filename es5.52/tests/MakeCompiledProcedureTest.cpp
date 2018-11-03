#include "../src/make_compiled_procedure.h"
#include "../src/cons.h"
#include "../src/symbol.h"
#include "../src/environment.h"
#include <gtest/gtest.h>
 
TEST(MakeCompiledProcedureTest, EntryAndEnv) { 
    MakeCompiledProcedure* operation = new MakeCompiledProcedure();
    Symbol* entry = new Symbol("my-entry-label");
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

