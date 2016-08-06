#ifndef MACHINE_H
#define MACHINE_H
#include <vector>
#include <map>
#include "data_structures.h"
#include "operation.h"
#include "instruction.h"

class Machine {
    private:
        int pc;
        std::map<Symbol,Operation*> operations;
        std::vector<Instruction*> the_instruction_sequence;
        std::vector<Instruction*> assemble(Value* controller_text);
        Instruction* compile(Value* instruction);
        void execute();
    public:
        Machine(std::vector<Value*> register_names, std::map<Symbol,Operation*> operations, Value* controller_text);
        void start();
};

#endif
