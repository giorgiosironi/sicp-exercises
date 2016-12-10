#include <string>
#include "is.h"
#include "integer.h"
#include "cons.h"
#include "nil.h"
#include "string.h"

bool is_number(Value *exp)
{
    if (Integer *schemeInteger = dynamic_cast<Integer *>(exp)) {
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

/**
 * Trick: compare the string representations, since we are talking about
 * simple data structures here. If we get a recurring pointer, this will explode
 */
bool is_eq(Value *former, Value *latter)
{
    return former->toString() == latter->toString();
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

bool is_begin(Value* exp)
{
    return is_tagged_list(exp, new Symbol("begin"));
}
