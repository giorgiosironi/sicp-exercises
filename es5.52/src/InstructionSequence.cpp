#include <typeinfo>
#include <algorithm>
#include <iostream>
#include "instruction_sequence.h"
#include "dump.h"
#include "nil.h"
// temporary:
#include "cons.h"
#include "integer.h"

using namespace std;

/*
 * 5.5.4
 * an instruction sequence is represented as a list of the registers needed, the registers modified, and
 * the actual instructions. We will also consider a label (symbol) to be a degenerate case of an instruction sequence,
 * which doesn't need or modify any registers. So to determine the registers needed and modified by instruction
 * sequences we use the selectors
 * TODO: Introduce Label class, which has a common superclass with InstructionSequence
 */
InstructionSequence::InstructionSequence(vector<Symbol*> needs, vector<Symbol*> modifies, Value* statements)
{
    this->_needs = needs;
    this->_modifies = modifies;
    this->_statements = statements;
}

vector<Symbol*> InstructionSequence::needs() {
    return this->_needs;
}

vector<Symbol*> InstructionSequence::modifies() {
    return this->_modifies;
}

Value* InstructionSequence::statements()
{
    return this->_statements;
}

string InstructionSequence::to_string() const
{
    return string("InstructionSequence(\n")
        + "    needs: " + ::to_string(this->_needs) + "\n"
        + "    modifies: " + ::to_string(this->_modifies) + "\n"
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
    if (this->_needs.size() != other._needs.size()) {
        return false;
    }
    if (!equal(
        begin(this->_needs),
        end(this->_needs),
        begin(other._needs),
        [](const Value* lhs, const Value* rhs){
            return *lhs == *rhs;
        }
    )) {
        return false;
    }
    if (this->_modifies.size() != other._modifies.size()) {
        return false;
    }
    if (!equal(
        begin(this->_modifies),
        end(this->_modifies),
        begin(other._modifies),
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

InstructionSequence* InstructionSequence::append(InstructionSequence* followUp) {
    return new InstructionSequence(
        vector<Symbol*>({ new Symbol("val") }), // sure about that?
        vector<Symbol*>({ new Symbol("val"), new Symbol("exp") }),
        Cons::from_vector({
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("val"),
                Cons::from_vector({
                    new Symbol("const"),
                    new Integer(42)
                })
            }),
            Cons::from_vector({
                new Symbol("assign"),
                new Symbol("exp"),
                Cons::from_vector({
                    new Symbol("reg"),
                    new Symbol("val"),
                })
            })
        })
    );
}

InstructionSequence* InstructionSequence::preserving(vector<Symbol*> registers, InstructionSequence* followUp) {
    return InstructionSequence::empty();
}

InstructionSequence* InstructionSequence::empty() {
    return new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>(),
        NIL
    );
}
