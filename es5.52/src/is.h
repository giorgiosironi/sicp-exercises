#ifndef IS_H
#define IS_H
#include "value.h"
#include "symbol.h"

bool is_number(Value *exp);
bool is_bool(Value *exp);
bool is_pair(Value *exp);
bool is_nil(Value *exp);
bool is_string(Value *exp);
bool is_eq(Value *former, Value *latter);
bool is_tagged_list(Value *exp);
bool is_tagged_list(Value *exp, Symbol* tag);
bool is_begin(Value* exp);

#endif
