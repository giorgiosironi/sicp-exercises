#include <string>
#include "is.h"
#include "scheme_integer.h"
#include "cons.h"
#include "nil.h"
#include "string.h"

bool is_number(Value *exp)
{
    if (SchemeInteger *schemeInteger = dynamic_cast<SchemeInteger *>(exp)) {
        return true;
    }
    return false;
}

bool is_pair(Value *exp)
{
    if (Cons *cons = dynamic_cast<Cons *>(exp)) {
        return true;
    }
    return false;
}

bool is_nil(Value *exp)
{
    if (Nil *nil = dynamic_cast<Nil *>(exp)) {
        return true;
    }
    return false;
}

bool is_string(Value *exp)
{
    if (String *string = dynamic_cast<String *>(exp)) {
        return true;
    }
    return false;
}
