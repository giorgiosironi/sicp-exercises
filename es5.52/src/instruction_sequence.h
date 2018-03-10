#ifndef INSTRUCTION_SEQUENCE_H
#define INSTRUCTION_SEQUENCE_H
#include <vector>
#include <set>
#include <iostream>
#include <string>
#include "../src/symbol.h"
#include "../src/list.h"
using namespace std;

class InstructionSequence {
    private:
        set<Symbol> _needsSet;
        set<Symbol> _modifiesSet;
        List* _statements;
    public:
        InstructionSequence(vector<Symbol*> needs, vector<Symbol*> modifies, List* statements);
        bool equals(const InstructionSequence& other) const;
        vector<Symbol*> needs();
        bool needs(Symbol* candidate);
        vector<Symbol*> modifies();
        bool modifies(Symbol* candidate);
        List* statements();
        string to_string() const;
        InstructionSequence* append(InstructionSequence* followUp);
        InstructionSequence* preserving(vector<Symbol*> registers, InstructionSequence* followUp);
        static InstructionSequence* empty();
};

bool operator==(const InstructionSequence& lhs, const InstructionSequence& rhs);
bool operator!=(const InstructionSequence& lhs, const InstructionSequence& rhs);

ostream& operator<<(ostream& os, const ::InstructionSequence& instructionSequence);

#endif
