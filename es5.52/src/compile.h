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
bool is_application(Value *exp);
InstructionSequence* compile_application(Value* exp, Symbol* target, Linkage* linkage);

bool is_if(Value *exp);
InstructionSequence* compile_if(Value* exp, Symbol* target, Linkage* linkage);

bool is_begin(Value *exp);
InstructionSequence* compile_sequence(List* seq, Symbol* target, Linkage* linkage);

InstructionSequence* construct_arg_list(vector<InstructionSequence*> operandCodes);
InstructionSequence* code_to_get_rest_args(vector<InstructionSequence*> operandCodes);
InstructionSequence* compile_procedure_call(Symbol* target, Linkage* linkage);

#endif
