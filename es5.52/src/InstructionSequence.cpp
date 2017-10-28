#include <typeinfo>
#include <algorithm>
#include <iostream>
#include "instruction_sequence.h"
using namespace std;

InstructionSequence::InstructionSequence(vector<Symbol*> needs, vector<Symbol*> modifies, Value* statements)
{
    this->needs = needs;
    this->modifies = modifies;
    this->statements = statements;
}

bool operator==(const InstructionSequence& lhs, const InstructionSequence& rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equals(rhs);
}

bool operator!=(const InstructionSequence& lhs, const InstructionSequence& rhs)
{
    return !(lhs == rhs);
}

bool InstructionSequence::equals(const InstructionSequence& other) const
{
    //https://stackoverflow.com/questions/39855341/equals-operator-on-stl-vector-of-pointers
    if (this->needs.size() != other.needs.size()) {
        return false;
    }
    if (!equal(
        begin(this->needs),
        end(this->needs),
        begin(other.needs),
        [](const Value* lhs, const Value* rhs){
            return *lhs == *rhs;
        }
    )) {
        return false;
    }
    if (this->modifies.size() != other.modifies.size()) {
        return false;
    }
    if (!equal(
        begin(this->modifies),
        end(this->modifies),
        begin(other.modifies),
        [](const Value* lhs, const Value* rhs){
            return *lhs == *rhs;
        }
    )) {
        return false;
    }
    if (*this->statements != *other.statements) {
        return false;
    }
    return true;
}
