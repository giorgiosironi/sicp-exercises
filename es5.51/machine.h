#ifndef MACHINE_H
#define MACHINE_H
#include <vector>
#include <map>
#include "data_structures.h"
#include "operation.h"
#include "instruction.h"
#include "register.h"
#include "stack.h"
#include "symbol.h"

class Machine {
    private:
        int pc;
        Register* flag;
        Stack* stack;
        std::map<std::string,Register*> registers;
        std::map<Symbol,Operation*> operations;
        std::vector<Instruction*> the_instruction_sequence;
        Instruction* compile(Value* instruction);
        Instruction* make_label_noop(Symbol* symbol);
        Instruction* make_perform(Cons* instruction);
        Instruction* make_assign(Cons* instruction);
        Instruction* make_goto(Cons* instruction);
        void execute();
    public:
        Machine();
        void allocate_register(std::string name);
        /**
         * Appends to the existing operations, does not replace
         */
        void install_operations(std::map<Symbol,Operation*> operations);
        void install_instruction_sequence(std::vector<Instruction*> instruction_sequence);
        std::vector<Instruction*> assemble(Value* controller_text);
        void start();
        void nextInstruction();
};

#endif
