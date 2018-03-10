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
    set<Symbol> needsSet;
    for (vector<Symbol*>::iterator it = needs.begin(); it != needs.end(); ++it) {
        needsSet.insert(**it);
    }
    this->_needsSet = needsSet;
    set<Symbol> modifiesSet;
    for (vector<Symbol*>::iterator it = modifies.begin(); it != modifies.end(); ++it) {
        modifiesSet.insert(**it);
    }
    this->_needsSet = needsSet;
    this->_modifiesSet = modifiesSet;
    this->_statements = statements;
}

vector<Symbol*> InstructionSequence::needs() {
    auto needs = vector<Symbol*>();
    for (set<Symbol>::iterator it = this->_needsSet.begin(); it != this->_needsSet.end(); ++it) {
        std::string name = (*it).name();
        needs.push_back(new Symbol(name));
    }

    return needs;
}

bool InstructionSequence::needs(Symbol* candidate) {
    return
        find_if(
            this->_needsSet.begin(),
            this->_needsSet.end(),
            [&candidate](Symbol e) { return e == *candidate; }
            )
        !=
        this->_needsSet.end()
    ;
}

vector<Symbol*> InstructionSequence::modifies() {
    auto modifies = vector<Symbol*>();
    for (set<Symbol>::iterator it = this->_modifiesSet.begin(); it != this->_modifiesSet.end(); ++it) {
        std::string name = (*it).name();
        modifies.push_back(new Symbol(name));
    }

    return modifies;
}

bool InstructionSequence::modifies(Symbol* candidate) {
    return
        find_if(
            this->_modifiesSet.begin(),
            this->_modifiesSet.end(),
            [&candidate](Symbol e) { return e == *candidate; }
            )
        !=
        this->_modifiesSet.end()
    ;
}

Value* InstructionSequence::statements()
{
    return this->_statements;
}

string InstructionSequence::to_string() const
{
    return string("InstructionSequence(\n")
        + "    needs: " + ::to_string(this->_needsSet) + "\n"
        + "    modifies: " + ::to_string(this->_modifiesSet) + "\n"
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
    if (this->_needsSet.size() != other._needsSet.size()) {
        return false;
    }
    if (!equal(
        begin(this->_needsSet),
        end(this->_needsSet),
        begin(other._needsSet),
        [](Symbol lhs, Symbol rhs){
            return lhs == rhs;
        }
    )) {
        return false;
    }
    if (this->_modifiesSet.size() != other._modifiesSet.size()) {
        return false;
    }
    if (!equal(
        begin(this->_modifiesSet),
        end(this->_modifiesSet),
        begin(other._modifiesSet),
        [](Symbol lhs, Symbol rhs){
            return lhs == rhs;
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
    Symbol* first = registers.at(0);
    if (followUp->needs(first) && this->modifies(first)) {
        registers.erase(registers.begin());

        auto new_needs = this->needs();
        if (!this->needs(first)) {
            new_needs.insert(new_needs.begin(), first);
        }
        auto new_modifies = this->modifies();

        auto found = find_if( new_modifies.begin(), new_modifies.end(), [&first](Symbol* e) { return *e == *first; });
        new_modifies.erase(found);
        auto wrapped = new InstructionSequence(
            new_needs,
            new_modifies,
            // TODO: add save/restore
            // (append `((save ,first-reg))
            //         (statements seq1)
            //         `((restore ,first-reg))))
            this->statements()
        );
        return wrapped->preserving(registers, followUp);
    } else {
        // inefficient, but what can you do
        registers.erase(registers.begin());
        auto tmp = this->preserving(registers, followUp);
        return tmp;
    }
}

InstructionSequence* InstructionSequence::empty() {
    return new InstructionSequence(
        vector<Symbol*>(),
        vector<Symbol*>(),
        NIL
    );
}
