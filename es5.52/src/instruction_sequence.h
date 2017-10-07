#ifndef INSTRUCTION_SEQUENCE_H
#define INSTRUCTION_SEQUENCE_H
#include <vector>
#include "../src/symbol.h"
using namespace std;

class InstructionSequence {
    public:
        InstructionSequence(vector<Symbol*> needs, vector<Symbol*> modifies, Value* statements);
        //virtual std::string to_string();
};

#endif
