#ifndef COMPILE_H
#define COMPILE_H
#include "value.h"
#include "symbol.h"
#include "instruction_sequence.h"

InstructionSequence* compile(Value* exp, Symbol* target);

#endif
