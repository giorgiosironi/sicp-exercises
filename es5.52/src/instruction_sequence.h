#ifndef INSTRUCTION_SEQUENCE_H
#define INSTRUCTION_SEQUENCE_H
#include <vector>
#include <iostream>
#include <string>
#include "../src/symbol.h"
using namespace std;

class InstructionSequence {
    private:
        vector<Symbol*> needs;
        vector<Symbol*> modifies;
        Value* _statements;
    public:
        InstructionSequence(vector<Symbol*> needs, vector<Symbol*> modifies, Value* statements);
        bool equals(const InstructionSequence& other) const;
        Value* statements();
        string to_string() const;
        InstructionSequence* preserving(vector<Symbol*> registers, InstructionSequence* followUp);
        static InstructionSequence* empty();
};

bool operator==(const InstructionSequence& lhs, const InstructionSequence& rhs);
bool operator!=(const InstructionSequence& lhs, const InstructionSequence& rhs);

ostream& operator<<(ostream& os, const ::InstructionSequence& instructionSequence);

#endif
