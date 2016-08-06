#ifndef IS_H
#define IS_H
#include "value.h"

bool is_number(Value *exp);
bool is_pair(Value *exp);
bool is_nil(Value *exp);
bool is_string(Value *exp);

#endif
