#ifndef INSTRUCTION_SEQUENCE_H
#define INSTRUCTION_SEQUENCE_H
#include <vector>
#include "../src/symbol.h"
using namespace std;

class InstructionSequence {
    private:
        vector<Symbol*> needs;
        vector<Symbol*> modifies;
        Value* statements;
    public:
        InstructionSequence(vector<Symbol*> needs, vector<Symbol*> modifies, Value* statements);
        bool equals(const InstructionSequence& other) const;
};

bool operator==(const InstructionSequence& lhs, const InstructionSequence& rhs);
bool operator!=(const InstructionSequence& lhs, const InstructionSequence& rhs);

#endif
