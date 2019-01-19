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

bool is_assignment(Value *exp);
InstructionSequence* compile_assignment(Value* exp, Symbol* target, Linkage* linkage);

bool is_quoted(Value *exp);
InstructionSequence* compile_quoted(Value* exp, Symbol* target, Linkage* linkage);
bool is_definition(Value *exp);
InstructionSequence* compile_definition(Value* exp, Symbol* target, Linkage* linkage);
bool is_application(Value *exp);
InstructionSequence* compile_application(Value* exp, Symbol* target, Linkage* linkage);

bool is_if(Value *exp);
InstructionSequence* compile_if(Value* exp, Symbol* target, Linkage* linkage);
bool is_cond(Value *exp);
Value* cond_to_if(Value *exp);
Value* sequence_to_exp(List *seq);
Value* expand_clauses(List* clauses);

bool is_let(Value *exp);


bool is_lambda(Value *exp);
InstructionSequence* compile_lambda(Value* exp, Symbol* target, Linkage* linkage);
InstructionSequence* compile_lambda_body(Value* exp, Symbol* proc_entry);

bool is_begin(Value *exp);
InstructionSequence* compile_sequence(List* seq, Symbol* target, Linkage* linkage);

InstructionSequence* construct_arg_list(vector<InstructionSequence*> operandCodes);
InstructionSequence* code_to_get_rest_args(vector<InstructionSequence*> operandCodes);
InstructionSequence* compile_procedure_call(Symbol* target, Linkage* linkage);

#endif
