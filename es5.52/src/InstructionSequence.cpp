#include <typeinfo>
#include <algorithm>
#include <iostream>
#include "instruction_sequence.h"
#include "dump.h"
#include "nil.h"
#include "conversion.h"
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

bool InstructionSequence::needs(Symbol* candidate) {
    return
        find_if(
            this->_needs.begin(),
            this->_needs.end(),
            [&candidate](Symbol* e) { return *e == *candidate; }
            )
        !=
        this->_needs.end()
    ;
}

vector<Symbol*> InstructionSequence::modifies() {
    return this->_modifies;
}

bool InstructionSequence::modifies(Symbol* candidate) {
    return
        find_if(
            this->_modifies.begin(),
            this->_modifies.end(),
            [&candidate](Symbol* e) { return *e == *candidate; }
            )
        !=
        this->_modifies.end()
    ;
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
    auto needed1 = this->needs();
    auto needed2 = followUp->needs();
    auto modified1 = this->modifies();
    auto modified2 = followUp->modifies();
    sort(needed2.begin(), needed2.begin()+needed2.size());
    sort(modified1.begin(), modified1.begin()+modified1.size());
    vector<Symbol*> difference;
    set_difference(
        needed2.begin(),
        needed2.begin()+needed2.size(),
        modified1.begin(),
        modified1.begin()+modified1.size(),
        inserter(difference, difference.end())
    );
    vector<Symbol*> new_needs;
    set_union(
        needed1.begin(),
        needed1.begin()+needed1.size(),
        difference.begin(),
        difference.begin()+difference.size(),
        inserter(new_needs, new_needs.end())
    );

    vector<Symbol*> new_modifies;
    set_union(
        modified1.begin(),
        modified1.begin()+modified1.size(),
        modified2.begin(),
        modified2.begin()+modified2.size(),
        inserter(new_modifies, new_modifies.end())
    );

    List* new_statements = convert_to<Cons>(this->_statements)->append_list(convert_to<List>(followUp->_statements));

    return new InstructionSequence(
        new_needs,
        new_modifies,
        new_statements
    );
}

InstructionSequence* InstructionSequence::preserving(vector<Symbol*> registers, InstructionSequence* followUp) {
    if (registers.empty()) {
        return this->append(followUp);
    }
    if (false) {
    } else {
        registers.erase(registers.begin());
        return this->preserving(registers, followUp);
    }
}

InstructionSequence* InstructionSequence::empty() {
    return new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>(),
        NIL
    );
}
