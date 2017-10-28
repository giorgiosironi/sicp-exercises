#ifndef COMPILE_H
#define COMPILE_H
#include "value.h"
#include "symbol.h"
#include "instruction_sequence.h"

InstructionSequence* compile(Value* exp, Symbol* target);
bool is_self_evaluating(Value* exp);
InstructionSequence* compile_self_evaluating(Value* exp, Symbol* target);

#endif
