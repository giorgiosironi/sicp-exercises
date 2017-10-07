#include "length.h"
#include "cons.h"
#include "is.h"

int length(Value *exp)
{
    if (is_pair(exp)) {
        Cons *cons = (Cons*) exp;
        return 1 + length(cons->cdr());
    }
    if (is_nil(exp)) {
        return 0;
    }
    // TODO: error
}

