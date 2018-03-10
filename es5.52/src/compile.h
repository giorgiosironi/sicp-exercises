#ifndef COMPILE_H
#define COMPILE_H
#include "value.h"
#include "symbol.h"
#include "instruction_sequence.h"
#include "linkage.h"

InstructionSequence* compile(Value* exp, Symbol* target, Linkage* linkage);
bool is_self_evaluating(Value* exp);
InstructionSequence* compile_self_evaluating(Value* exp, Symbol* target, Linkage* linkage);
bool is_variable(Value *exp);
InstructionSequence* compile_variable(Value* exp, Symbol* target, Linkage* linkage);
bool is_quoted(Value *exp);
InstructionSequence* compile_quoted(Value* exp, Symbol* target, Linkage* linkage);
bool is_definition(Value *exp);
InstructionSequence* compile_definition(Value* exp, Symbol* target, Linkage* linkage);

#endif
