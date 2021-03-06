#include <string>
#include "is.h"
#include "integer.h"
#include "float.h"
#include "bool.h"
#include "cons.h"
#include "nil.h"
#include "string.h"

bool is_number(Value *exp)
{
    if (Integer *schemeInteger = dynamic_cast<Integer *>(exp)) {
        return true;
    }
    if (Float *schemeFloat = dynamic_cast<Float *>(exp)) {
        return true;
    }
    return false;
}

bool is_bool(Value *exp)
{
    if (Bool *boolean = dynamic_cast<Bool *>(exp)) {
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

bool is_eq(Value *former, Value *latter)
{
    return *former == *latter;
}

bool is_tagged_list(Value *exp)
{
    if (is_pair(exp)) {
        return true;
    }
    return false;
}

bool is_tagged_list(Value *exp, Symbol* tag)
{
    if (is_pair(exp)) {
        Cons *expAsPair = (Cons *) exp;
        return is_eq(expAsPair->car(), tag);
    }
    return false;
}
