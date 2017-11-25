#include <typeinfo>
#include <algorithm>
#include <iostream>
#include "instruction_sequence.h"
#include "dump.h"
#include "nil.h"
using namespace std;

InstructionSequence::InstructionSequence(vector<Symbol*> needs, vector<Symbol*> modifies, Value* statements)
{
    this->needs = needs;
    this->modifies = modifies;
    this->_statements = statements;
}

Value* InstructionSequence::statements()
{
    return this->_statements;
}

string InstructionSequence::to_string() const
{
    return string("InstructionSequence(\n")
        + "    needs: " + ::to_string(this->needs) + "\n"
        + "    modifies: " + ::to_string(this->modifies) + "\n"
        + "    statements: " + this->_statements->to_string() + "\n";
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
    if (*this->_statements != *other._statements) {
        return false;
    }
    return true;
}

ostream& operator<<(ostream& os, const ::InstructionSequence& instructionSequence) {
    return os << instructionSequence.to_string();
}

InstructionSequence* InstructionSequence::empty() {
    return new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>(),
        NIL
    );
}
